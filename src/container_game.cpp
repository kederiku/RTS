#include "container_game.h"
#include "ressources.h"
#include "point.h"
#include "ui.hpp"
#include "ui.h"
#include "ns_var.h"
#include "building.h"
#include "list.hpp"
#include "env.hpp"
#include <new>
#include "archery_range.h"
#include "barrack.h"
#include "house.h"
#include "stable.h"
#include "tower.h"
#include "town_center.h"
#include "game.h"
#include "building.h"
#include "map.h"
#include "s_ressources.h"

Container_game::Container_game(void): __units(false)
{
	this->__pos.x = 0;
	this->__pos.y = 0;
}

Container_game::~Container_game(void)
{
}

bool	Container_game::new_case(const Point& sprite, const Point& dest)
{
	Lib2D::Subimage	subimage;

	if (Env::get_instance()->ressource.init_subimage_sprite_field(&subimage, sprite, this->__map.get_size_case()) == false)
		return false;
	subimage.move(dest.x * 32, dest.y * 32);
	if (this->__blitable->blit(&subimage) == false)
		return false;
	return true;
}

bool	Container_game::load_cases_map(void)
{
	Point		dest;
	Point		sprite;

	dest.y = 0;
	while (dest.y  < this->__map.get_height())
	{
		dest.x = 0;
		while (dest.x < this->__map.get_width())
		{
			this->__map.get_pos_img(dest, &sprite);
			if (this->new_case(sprite, dest) == false)
				return false;
			++dest.x;
		}
		++dest.y;
	}
	return true;
}

bool	Container_game::load_ressource(void)
{
	std::vector<data_ressource>		data;
	std::vector<data_ressource>::iterator	it_begin;
	std::vector<data_ressource>::iterator	it_end;

	if (this->__map.get_ressource(data) == false)
		return false;
	it_begin = data.begin();
	it_end = data.end();
	while (it_begin != it_end)
	{
		if (this->new_ressource(it_begin->ressource, it_begin->pos) == false)
			return false;
		++it_begin;
	}
	return true;
}

bool	Container_game::init_map(void)
{
	if (this->load_cases_map() == false)
		return false;
	if (this->load_ressource() == false)
		return false;
//	if (this->load_building() == false)
//		return false;
	return true;
}

bool	Container_game::init_new_map(void)
{
	Point	sprite(15 * 33, 18 * 33);
	Point	pos;

	pos.y = 0;
	while (pos.y  < this->__map.get_height())
	{
		pos.x = 0;
		while (pos.x < this->__map.get_width())
		{
			this->__map.set_case(pos.x, pos.y, sprite, false);
			++pos.x;
		}
		++pos.y;
	}
	return true;
}

bool	Container_game::init_container(int width, int height)
{
	this->__width = width;
	this->__heigh = height;
	if (this->__sprite_ressource.load_bmp(RES) == false)
		return false;
	if (this->Container::init() == false)
		return false;
	this->move(0, 0);
	this->resize(this->__map.get_width() * this->__map.get_size_case(),
		     this->__map.get_height() * this->__map.get_size_case());
	this->__blitable = new (std::nothrow) Lib2D::Blitable;
	if (add_children(this, this->__blitable) == false ||
			 this->__blitable->init(this->__map.get_width() * this->__map.get_size_case(),
						this->__map.get_height() * this->__map.get_size_case()) == false)
		return false;
	return true;
}

bool	Container_game::init(int nb_case_width, int nb_case_height, int width, int height)
{
	if (this->__map.init(32, nb_case_width, nb_case_height) == false)
		return false;
	if (this->init_container(width, height) == false)
		return false;
	if (this->init_new_map() == false)
		return false;
	if (this->init_map() == false)
		return false;
	return true;
}

bool	Container_game::init(const char* path, int width, int height)
{
	if (this->__map.load_file(path) == false)
		return false;
	if (this->init_container(width, height) == false)
		return false;
	if (this->init_map() == false)
		return false;
	return true;
}

bool	Container_game::derived_treat_event(Lib2D::Event* event)
{
	if (event->get_type() == Lib2D::E_KEYDOWN_EVENT)
	{
		if (((Lib2D::Keyboard_event*)event)->get_key_char() == 273)
			this->__scrolling = UP;
		else if (((Lib2D::Keyboard_event*)event)->get_key_char() == 274)
			this->__scrolling = DOWN;
		else if (((Lib2D::Keyboard_event*)event)->get_key_char() == 275)
			this->__scrolling = LEFT;
		else if (((Lib2D::Keyboard_event*)event)->get_key_char() == 276)
			this->__scrolling = RIGHT;
	}
	else if (event->get_type() == Lib2D::E_KEYUP_EVENT)
		this->__scrolling = SNONE;
	
	else if (event->get_type() == Lib2D::E_MOUSEMOTION_EVENT)
	{
		if (((Lib2D::Mouse_event*)event)->get_mouse_event()->x > 890)
			this->__scrolling = LEFT;
		else if (((Lib2D::Mouse_event*)event)->get_mouse_event()->y > 790)
			this->__scrolling = DOWN;
		else if (((Lib2D::Mouse_event*)event)->get_mouse_event()->x < 20)
			this->__scrolling = RIGHT;
		else if (((Lib2D::Mouse_event*)event)->get_mouse_event()->y < 20)
			this->__scrolling = UP;
		else
			this->__scrolling = SNONE;
	}
	
	return true;
}

bool	Container_game::derived_treat_render(void)
{
//	this->debug_collision();
	int	move(this->__map.get_size_case());


	if (this->__scrolling == LEFT &&
	   (-(this->__pos.x - this->__width) <= (int)this->_pos.w))
	{
		this->__pos.x -= move;
		this->move(this->__pos.x, this->__pos.y);
	}
	else if (this->__scrolling == DOWN &&
		(-(this->__pos.y - move - this->__heigh) <= (int)this->_pos.h))
	{
		this->__pos.y -= move;
		this->move(this->__pos.x, this->__pos.y);
	}
	else if (this->__scrolling == RIGHT && this->__pos.x + move <= 0)
	{
		this->__pos.x += move;
		this->move(this->__pos.x, this->__pos.y);
	}
	else if (this->__scrolling == UP && this->__pos.y + move <=  0)
	{
		this->__pos.y += move;
		this->move(this->__pos.x, this->__pos.y);
	}
	return true;
}

/*
bool	Container_game::treat_event(Lib2D::Event*)
{
	return true;
}
bool	Container_game::treat_render(void)
{
	return false;
	return true;
}
*/

void	Container_game::move_map(const Point& center)
{
	Point	size(this->__width / 2, this->__heigh / 2);

	if (center.x < size.x)
		this->__pos.x = 0;
	else if (center.x + this->__width > (int)this->_pos.w)
		this->__pos.x = -this->_pos.w + this->__width;
	else
		this->__pos.x = -center.x + size.x;
	if (center.y < size.y)
		this->__pos.y = 0;
	else if (center.y + this->__heigh > (int)this->_pos.h)
		this->__pos.y = -this->_pos.h + this->__heigh;
	else
		this->__pos.y = -center.y + size.y;
	this->move(this->__pos.x, this->__pos.y);
}

bool	Container_game::save(const char* file)
{
	if (this->__map.is_init() == false)
		return false;
	return this->__map.save_file(file);
}

bool	Container_game::new_ressource(e_ressource type, const Point& dest)
{
	Ressources*	subimage;
	int		capacity(0);

	if (type == GOLD)
		capacity = 5000;
	else if (type == WOOD)
		capacity = 100;
	subimage = new (std::nothrow) Ressources;
	if (subimage == 0 || add_children(this, subimage) == false || subimage->init(type, capacity, this, &this->__map) == false)
		return false;
	subimage->move(dest.x, dest.y);
	this->__map.set_case_ressource(dest, Point(subimage->pos().w, subimage->pos().h), subimage);
	return true;
}

bool	Container_game::add_field(const Point& sprite_pos, const Point& mouse)
{
	Point	pos(mouse.x - this->__pos.x, mouse.y - this->__pos.y);

	pos.x /= 32;
	pos.y /= 32;
	this->__map.set_case(pos.x, pos.y, sprite_pos, false);
	if (this->new_case(sprite_pos, pos) == false)
		return false;
	return true;
}


bool	Container_game::add_ressource(e_ressource ressource, const Point& mouse)
{
	Point		pos(mouse.x - this->__pos.x, mouse.y - this->__pos.y);
	info_ressource	info;
	Point		size;

	pos.x /= 32;
	pos.y /= 32;
	pos.x *= 32;
	pos.y *= 32;
	if (Env::get_instance()->ressource.get_info_ressource(&info, ressource) == false)
		return false;
	size.x = info.w;
	size.y = info.h;
	if (this->__map.add_ressource(pos, size, ressource, 100) == false ||
	    this->new_ressource(ressource, pos) == false)
		return false;
	return true;
}

bool	Container_game::check_pos_construction(Lib2D::Control* check) const
{
	Point		pos(check->pos().x - this->__pos.x, check->pos().y - this->__pos.y);

	return this->__map.check_collision_construction(pos, check);
}

bool	Container_game::add_building(Lib2D::Control* ctrl, e_type building_type, int id_player)
{
	Point	pos(ctrl->pos().x - this->__pos.x, ctrl->pos().y - this->__pos.y);

	return Env::get_instance()->client.send_building(pos, building_type, id_player);
}

Map*	Container_game::get_map(void)
{
	return &this->__map;
}

void	Container_game::get_pos(const Point& mouse, Point* ret)
{
	ret->x = mouse.x - this->__pos.x;
	ret->y = mouse.y - this->__pos.y;
}

void	Container_game::debug_collision(void)
{
	unsigned		x;
	unsigned		y(0);
	Lib2D::Subimage		subimage;
	Point			sprite(0);

	for (;y < 200; ++y)
		for (x = 0;x < 200; ++x)
		{
			subimage.move(x * 32, y * 32);
			if (this->__map.is_case_valid(x, y) == false)
				sprite = 0;
			else
				this->__map.get_pos_img(Point(x, y), &sprite);
			Env::get_instance()->ressource.init_subimage_sprite_field(&subimage, sprite, 32);
			this->__blitable->blit(&subimage);
		}
}




void	Container_game::select(const Point& mouse)
{
	this->get_pos(mouse, &this->__select_units);
	this->__select_units.x /= 32;
	this->__select_units.y /= 32;
	this->__units = true;
}


bool	Container_game::select_units(const Point& mouse, std::list<Unit*>& units, int id_player)
{
	Point	real_pos;

	this->get_pos(mouse, &real_pos);
	real_pos.x /= 32;
	real_pos.y /= 32;
	if (this->__units == false)
		return true;
	this->__units = false;
	if (this->__select_units == real_pos)
		return this->add_units(real_pos.x, real_pos.y, units, id_player);
	return this->multi_select(real_pos, units, id_player);

}

bool	Container_game::multi_select(const Point& end, std::list<Unit*>& list, int id_player)
{
	if (this->__select_units.x < end.x && this->__select_units.y < end.y)
		return this->selection(this->__select_units, end, 1, 1, list, id_player);
	else if (this->__select_units.x > end.x && this->__select_units.y < end.y)
		return this->selection(this->__select_units, end, -1, 1, list, id_player);
	else if (this->__select_units.x < end.x && this->__select_units.y > end.y)
		return this->selection(this->__select_units, end, 1, -1, list, id_player);
	else if (this->__select_units.x > end.x && this->__select_units.y > end.y)
		return this->selection(this->__select_units, end, -1, -1, list, id_player);
	return true;
}


bool	Container_game::selection(const Point& begin, const Point& end, int x, int y, std::list<Unit*>& list, int id_player)
{
	Point	tmp(begin);

	while (tmp.x != end.x)
	{
		tmp.y = begin.y;
		while (tmp.y != end.y)
		{
			if (list.size() == 10)
				return true;
			if (this->add_units(tmp.x, tmp.y, list, id_player) == false)
				return false;
			tmp.y += y;
		}
		tmp.x += x;
	}
	return true;
}


bool	Container_game::add_units(unsigned x, unsigned y, std::list<Unit*>& list, int id_player)
{
	Unit*	units;

	units = this->__map.get_unit(x, y, id_player);
	if (units == 0)
		return true;
	try
	{
		list.push_back(units);
	}
	catch (std::bad_alloc&)
	{
		return false;
	}
	return true;
}
