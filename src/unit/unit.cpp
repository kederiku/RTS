#include "unit.h"
#include "ressources.h"
#include "env.hpp"
#include "map.h"
#include "astar.hpp"
#include "inter.h"

Unit::Unit(const char* name, int hp, int power, int portee, int build_time, int id_player)
	  : Info(name, hp, power, portee * 10, build_time, id_player, IUNIT), __frame(BOTTOM), __id_frame(4), __action(0)
{
	this->__state = UNONE;
	this->__destination = 0;
	this->__producer = 0;
	this->__id = -1;
	this->__inter = 0;
	if (id_player != -1)
	{
		this->__id = nb_unit;
		++nb_unit;
	}
	this->__unit_to_attack = 0;
}

bool	Unit::init(void)
{
	if (Env::get_instance()->ressource.init_subimage_units(this, this->__type) == false)
		return false;
	this->__sprite_animation = this->_rect.y;
	this->set_animation(BOTTOM);
	if (this->init_life() == false)
		return false;
	return true;
}

void	Unit::init_astar(Map* map)
{
	this->__astar.init(map, &this->__path, this);
	this->__map = map;
}

void	Unit::is_action(bool action, Info* unit)
{
	if (action == true)
	{
		this->__state = UACTION;
		this->__unit_to_attack = unit;
	}
	else
		this->__state = USLEEP;
	Env::get_instance()->state.set_attack_unit(true);
}

bool	Unit::action(Info* unit, int hp_to_remove)
{
	bool	ret = true;

	ret =  unit->set_hp(-hp_to_remove);
	if (ret == false)
		Env::get_instance()->state.set_attack_unit(false);
	return ret;
}

bool	Unit::set_hp(int add)
{
	if (this->Info::set_hp(add) == false)
	{
		this->__state = UDEAD;
		return false;
	}
	return true;
}

e_unit_state	Unit::get_state(void)
{
	return this->__state;
}

Point*	Unit::get_destination(void)
{
	return &this->__destination;
}

bool	Unit::set_destination(const Point& dest)
{
	while (this->__order.empty() == false)
		this->__order.pop();
	this->__destination = dest;
	if (this->add_order(&Unit::search_path) == false)
		return false;
	return true;
}

bool	Unit::is_destroyed(void)
{
	if (this->__hp > 0)
		return false;
	else
		return true;
}

void	Unit::begin_product(void)
{
	this->__timer.start();
}

void	Unit::construction_complete(void)
{
	this->__state = UCONSTRUCT;
}

bool	Unit::is_construction_complete(void)
{
	if (this->__timer.get_ticks() < this->__build_time * 1000)
		return false;
	this->__timer.stop();
	return true;
}

void	Unit::begin_attack(void)
{
	this->__timer.start();
}

bool	Unit::is_attack_complete(void)
{
	if (this->__timer.get_ticks() < 2000)
		return false;
	this->__timer.stop();
	return true;
}

unit_type	Unit::get_type(void)
{
	return this->__type;
}

int		Unit::get_id_player(void)
{
	return this->__id_player;
}

void		Unit::set_producer(Building* copy)
{
	this->__producer = copy;
}

Building*	Unit::get_producer(void)
{
	return this->__producer;
}

bool		Unit::add_order(int (Unit::*fct)(void))
{
	ptr_fct	order;

	order.fct = fct;
	try
	{
		this->__order.push(order);
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}


int		Unit::search_path(void)
{
	Point	pos(this->_pos.x / 32, this->_pos.y / 32);
	Point	dest(this->__destination.x / 32, this->__destination.y / 32);

	if (this->__astar.search_way(pos, dest) == false)
		return -1;
	if (this->__path.empty() == true)
		return 1;
	this->__state = UMOVE;
	if (this->add_order(&Unit::set_next_case) == false)
		return -1;
	return 0;
}

int		Unit::set_next_case(void)
{
	if (this->__path.empty() == true)
	{
		this->stop_animation();
		if (this->__action != 0)
		{
			if (this->add_order(this->__action) == false)
				return -1;
			return 0;
		}
		return 2;
	}
	this->__next_case = this->__path.front();
	if (this->add_order(&Unit::move_to_dest) == false)
		return -1;
	return 0;
}

int		Unit::move_to_dest(void)
{
	int		speed(8);
	Point		size(this->_pos.w, this->_pos.h);
	Point		next_pos(this->_pos.x, this->_pos.y);
	position	pos;

	if (this->_pos.x < this->__next_case.x * 32)
	{
		++pos.x;
		next_pos.x += speed;
	}
	else if (this->_pos.x  > this->__next_case.x * 32)
	{
		--pos.x;
		next_pos.x -=speed;
	}
	if (this->_pos.y  < this->__next_case.y * 32)
	{
		--pos.y;
		next_pos.y += speed;
	}
	else if (this->_pos.y  > this->__next_case.y * 32)
	{
		++pos.y;
		next_pos.y -= speed;
	}
	if (this->__map->is_case_valid(this->__next_case, next_pos, this) == false)
	{
		this->stop_animation();
		return 2;
	}
	this->change_animation(pos);
	this->__map->set_unit(this->_pos.x / 32, this->_pos.y / 32, 0);
	this->move(next_pos.x, next_pos.y);
	this->__map->set_unit(this->_pos.x / 32, this->_pos.y / 32, this);
	if (this->_pos.x  == this->__next_case.x * 32 && this->_pos.y  == this->__next_case.y * 32)
	{
		this->__path.pop_front();
		return 1;
	}
	return 0;
}


bool	Unit::derived_treat_render(void)
{
	Point	dest;
	int	ret;
	int	i(0);

	if (Info::derived_treat_render() == false)
		return false;
	if (this->__order.empty() == true)
		return true;
	ret = (this->*(this->__order.top().fct))();
	if (ret == -1)
		return false;
	while (i < ret)
	{
		this->__order.pop();
		++i;
	}
	return true;
}

void	Unit::move(int32_t x, int32_t y)
{

	Object::move(x, y);
	if (this->__life != 0)
		this->__life->move(x, y);
}

Info*	Unit::get_unit_to_attack(void)
{
	return this->__unit_to_attack;
}

void	Unit::change_animation(const position& pos)
{
	if (pos.x == 1)
	{
		if (pos.y == 1)
			this->set_animation(TOP_RIGHT);
		else if (pos.y == 0)
			this->set_animation(RIGHT);
		else if (pos.y == -1)
			this->set_animation(BOTTOM_RIGHT);
	}
	else if (pos.x == 0)
	{
		if (pos.y == 1)
			this->set_animation(TOP);
		else if (pos.y == -1)
			this->set_animation(BOTTOM);
	}
	else if (pos.x == -1)
	{
		if (pos.y == 1)
			this->set_animation(TOP_LEFT);
		else if (pos.y == 0)
			this->set_animation(LEFT);
		else if (pos.y == -1)
			this->set_animation(BOTTOM_LEFT);
	}
}

void	Unit::set_animation(unit_animation anim)
{
	if (this->__id_frame == 5 || this->__frame != anim)
		this->__id_frame = 0;
	this->__frame = anim;
	this->_rect.x = this->_rect.w * this->__id_frame;
	this->_rect.y = this->__sprite_animation + this->_rect.h * this->__frame;
	++this->__id_frame;
}

void	Unit::set_frame(int frame)
{
	this->__id_frame = frame;
	this->_rect.x = this->_rect.w * this->__id_frame;
}

void	Unit::stop_animation(void)
{
	this->__state = USLEEP;
	this->set_frame(4);
}

int	Unit::get_ressource(void)
{
	return this->__order.size();
}

int	Unit::search_ressource(void)
{
	return this->__order.size();
}

int	Unit::back_town_center(void)
{
	return this->__order.size();
}


int	Unit::drop_ressource(void)
{
	return this->__order.size();
}

Inter*
Unit::Get_Interface(void)
{
	return this->__inter;
}

void
Unit::Set_Interface(void)
{
	this->__inter = 0;
}

bool
Unit::Init_Interface(void)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image = 0;

	if (img_source.load_bmp(ICON) == false)
		return false;
	if ((this->__inter = new (std::nothrow)Inter) == 0)
		return false;
	image = img_source.get_image_part(this->__iconpoint.x, this->__iconpoint.y, 50, 50);
	if (image == 0)
	{
		delete this->__inter;
		return false;
	}
	return this->__inter->Head_Inter_Unit(image, this->__name, this);
}
