#include "academy.h"
#include "archer.h"
#include "archery_range.h"
#include "barrack.h"
#include "building.h"
#include "building_interface.h"
#include "container_game.h"
#include "druide.h"
#include "env.hpp"
#include "game.h"
#include "house.h"
#include "interface.h"
#include "knight.h"
#include "mage.h"
#include "nation.h"
#include "peon.h"
#include "player.h"
#include "ressources.h"
#include "stable.h"
#include "temple.h"
#include "tower.h"
#include "town_center.h"
#include "ui.hpp"
#include "unit.h"
#include "warrior.h"
#include "s_ressources.h"

unsigned	Unit::nb_unit = 0;
unsigned	Building::nb_building = 0;

Game::Game(void): __inter(0), __building(0), __new_building(0), __nb_player(0)
{
}

Game::~Game(void)
{
}

bool
Game::Init_game(Player** player, int id_mainplayer)
{
	int	i = 0;

	this->__id_mainplayer = id_mainplayer;
	try
	{
		this->__interface = new Interface;
		while (player[i] != 0)
		{
			this->__player.push_back(player[i]);
			i++;
		}
		this->__nb_player = i;
	}
	catch(...)
	{
		return false;
	}
	this->resize(900, 800);
	this->move(0, 0);
	if (Container::init() == false)
	{
		delete this->__interface;
		return false;
	}
	this->__container_game = new (std::nothrow) Container_game;
	if (this->__container_game == 0)
		return false;
	this->__container_game->move(0, 0);
	if (this->__container_game->init("200") == 0)
		return false;
	i = this->__container_game->children();
	Ressources*	ressource;
	while (i > 1)
	{
		ressource = (Ressources*)this->__container_game->get_child(i - 1);
		ressource->signals.add(Lib2D::make_func(this, &Game::inter_ressources), ressource, 0);
		i--;
	}
	if (add_children(this, this->__container_game) == false)
		return false;
	if (Container::init() == false || this->__interface->init(this, this->__player[this->__id_mainplayer]->get_nation()->get_land()) == false)
	{
		delete this->__interface;
		return false;
	}
	if (this->init_towncenter() == false)
	{
		delete this->__interface;
		return false;
	}
	return true;
}

bool	Game::inter_ressources(Lib2D::Control* control, void* data)
{
	(void)data;
	Ressources*	ressource = (Ressources*)control;

	if (this->__inter != 0)
		this->del_child(this->__inter);
	this->__interface->set_visible_building(false);
	if (ressource->Init_Interface() == false)
		return false;
	this->__inter = ressource->Get_Interface();
	this->add_child(this->__inter);
	return true;
}

bool	Game::init_towncenter(void)
{
	Point		townpos[] = {Point(400, 400), Point(2400, 400), Point(400, 2400), Point(2400, 2400)};
	unsigned	i(0);

	while (i < this->__player.size())
	{
		if (this->create_towncenter(i, townpos[i]) == false)
			return false;
		++i;
	}
	return true;
}


bool	Game::create_towncenter(int i, const Point& pos)
{
	Town_Center*	town_center;

	town_center = new (std::nothrow)Town_Center("Town Center", this->__player[i]->get_id_player());
	if (add_children(this->__container_game, town_center, false) == false)
		return false;
	town_center->move(pos.x, pos.y);
	if (town_center->init() == false)
		return false;
	if (this->__player[i]->add_building(town_center) == false)
		return false;
	if (this->__id_mainplayer == i && town_center->signals.add(Lib2D::make_func(this, &Game::Build), town_center, 0) == false)
		return false;
	if (this->__id_mainplayer != i && town_center->signals.add(Lib2D::make_func(this->__player[this->__id_mainplayer], &Player::select_unit_to_attack), town_center, 0) == false)
		return false;
	town_center->construction_complete();
	this->__container_game->get_map()->set_building(town_center);
	if (i == this->__id_mainplayer)
		this->__container_game->move_map(pos);
	return true;
}

bool	Game::is_in_container_map(const Lib2D::s_mouse_event* mouse_event) const
{
	return (mouse_event->x + (this->__new_building->pos().w / 2) < this->__container_game->pos().w &&
		mouse_event->y + (this->__new_building->pos().h / 2) < this->__container_game->pos().h  + 70 &&
		mouse_event->x > 0 && mouse_event->y > 70);
}

bool
Game::derived_treat_render(void)
{
	if (this->check_new_building() == false)
		return false;
	if (Env::get_instance()->state.get_building_in_construct() == true)
	{
		if (this->check_complete_construction() == false)
			return false;
	}
	if (this->check_new_unit() == false)
		return false;
	if (Env::get_instance()->state.get_unit_in_construct() == true)
	{
		if (this->complete_unit_construction() == false)
			return false;
	}
	if (this->check_attack() == false)
		return false;
	if (Env::get_instance()->state.get_attack_unit() == true)
	{
		if (this->__player[this->__id_mainplayer]->unit_attack() == false)
			return false;
	}
	if (Env::get_instance()->state.get_attack_time() == true)
		this->__player[this->__id_mainplayer]->unit_time();
	if (this->check_move_unit() == false)
		return false;
	if (this->__interface->check_ressource(this->__player[this->__id_mainplayer]) == false)
		return false;
	return true;
}

bool	Game::move_new_building(const Lib2D::s_mouse_event* mouse)
{
	if (this->__new_building == 0)
		return true;
	if (this->is_in_container_map(mouse))
	{
		this->__new_building->move(mouse->x - this->__new_building->pos().w / 2,
					   mouse->y - this->__new_building->pos().h / 2);
		this->__new_building->visible(true);
	}
	else
		this->__new_building->visible(false);
	return true;
}


void	Game::move_units(const Point& mouse_event)
{
	Point	dest;

	this->__container_game->get_pos(mouse_event, &dest);
	this->__player[this->__id_mainplayer]->send_move(dest, this->__container_game->get_map());
}

void	Game::del_interface_building(void)
{
	this->del_child(this->__inter);
	this->__inter = 0;
	this->__interface->set_visible_building(true);
}

bool	Game::select_units(const Point& mouse)
{
	std::list<Unit*>		units;

	if (this->__container_game->select_units(mouse, units, this->__id_mainplayer) == false)
		return false;
	std::list<Unit*>::iterator		it(units.begin());
	std::list<Unit*>::iterator		it_end(units.end());
	while (it != it_end)
	{
		this->__is_select = true;
		++it;
	}
	if (units.empty() == false)
		this->__player[this->__id_mainplayer]->change_select_units(units);
	return true;
}

bool
Game::derived_treat_event(Lib2D::Event* event)
{
	Point	mouse;

	if (event->get_type() == Lib2D::E_MOUSEMOTION_EVENT)
		return this->move_new_building(event->get_mouse_event());
	else if (event->get_type() == Lib2D::E_MOUSEDOWN_EVENT)
	{
		mouse.x = event->get_mouse_event()->x;
		mouse.y = event->get_mouse_event()->y;
		if (this->__new_building == 0)
		{
			if (event->get_mouse_event()->button == Lib2D::E_BUTTON_RIGHT)
			{
				this->move_units(mouse);
				if (this->__is_select == false)
					this->del_interface_building();
			}
			else if (event->get_mouse_event()->button == Lib2D::E_BUTTON_LEFT)
			{
				this->__player[this->__id_mainplayer]->unselect_unit();
				if (this->__is_select == true)
					this->del_interface_building();
				this->__is_select = false;
				this->__container_game->select(mouse);
			}
		}
		else if (this->__new_building != 0 && this->is_in_container_map(event->get_mouse_event()) == true
			 && event->get_mouse_event()->button == Lib2D::E_BUTTON_LEFT)
		{
			if (this->__container_game->check_pos_construction(this->__new_building) == true)
				return true;
			if (this->__container_game->add_building(this->__new_building, this->__building_type, this->__id_mainplayer) == false)
				return false;
			this->del_child(this->__new_building);
			this->__new_building = 0;
		}
	}
	else if (this->__new_building == 0 && event->get_type() == Lib2D::E_MOUSEUP_EVENT)
	{
		mouse.x = event->get_mouse_event()->x;
		mouse.y = event->get_mouse_event()->y;
		return this->select_units(mouse);
	}
	return true;
}

bool	Game::Create_Building(Lib2D::Control*, void* b)
{
	Building*		building = (Building*)b;

	if (building->get_costs().wood > this->__player[this->__id_mainplayer]->get_wood() || building->get_costs().gold > this->__player[this->__id_mainplayer]->get_gold())
		return false;
	if (building->get_type() == HOUSE && this->__player[this->__id_mainplayer]->get_employed_max() + 10 > 200)
		return false;
	if (this->__new_building != 0)
	{
		this->del_child(this->__new_building);
		this->__new_building = 0;
	}
	this->__new_building = new (std::nothrow) Lib2D::Subimage;
	if (this->__new_building == 0 ||
	    Env::get_instance()->ressource.init_subimage_building(this->__new_building, building->get_type()) == false ||
	    add_children(this, this->__new_building) == false)
	{
		delete this->__new_building;
		this->__new_building = 0;
		return false;
	}
	this->__building = building;
	this->__new_building->visible(false);
	this->__building_type = building->get_type();
	return true;
}

bool
Game::Build(Lib2D::Control* a, void*)
{
	Building*	building = (Building*)a;

	if (this->__inter != 0)
		this->del_child(this->__inter);
	this->__interface->set_visible_building(false);
	if (building->Init_Interface(this->__player[this->__id_mainplayer]) == false)
		return false;
	this->add_child(building->Get_Interface());
	this->__inter = building->Get_Interface();
	return true;
}

bool	Game::check_new_building(void)
{
	info_building*	info;
	Building*	building(0);

	info = Env::get_instance()->client.get_msg<info_building>();
	if (info == 0)
		return true;
	switch (info->id_build)
	{
		case HOUSE :
			building = new (std::nothrow) House("House", info->player);
			break;
		case BARRACK :
			building = new (std::nothrow) Barrack("Barrack", info->player);
			break;
		case TEMPLE :
			building = new (std::nothrow) Temple("Temple", info->player);
			break;
		case ACADEMY :
			building = new (std::nothrow) Academy("Academy", info->player);
			break;
		case ARCHERY_RANGE:
			building = new (std::nothrow) Archery_Range("Archery Range", info->player);
			break;
		case STABLE :
			building = new (std::nothrow) Stable("Stable", info->player);
			break;
		case TOWER :
			building = new (std::nothrow) Tower("Tower", info->player);
			break;
		case TOWN_CENTER :
			building = new (std::nothrow) Town_Center("Town Center", info->player);
			break;
	}
	building->move(info->pos.x, info->pos.y);
	this->__player[info->player]->set_wood(-building->get_costs().wood);
	this->__player[info->player]->set_gold(-building->get_costs().gold);
	if (add_children(this->__container_game, building) == false || building->init() == false)
		return false;
	this->__container_game->get_map()->set_building(building);
	Env::get_instance()->client.remove_buffer_read(info->size);
	Env::get_instance()->state.set_building_in_construct(true);
	try
	{
		this->__building_in_construct.push_back(building);
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}

bool	Game::complete_construction(Building* building)
{
	int	id_player = building->get_id_player();

	if (building->get_type() == HOUSE)
		building->product(this->__player[id_player], 0, 0);
	if(this->__player[id_player]->add_building(building) == false)
		return false;
	if (this->__id_mainplayer == id_player && building->signals.add(Lib2D::make_func(this, &Game::Build), building, 0) == false)
		return false;
	if (this->__id_mainplayer != id_player && building->signals.add(Lib2D::make_func(this->__player[this->__id_mainplayer], &Player::select_unit_to_attack), building, 0) == false)
		return false;
	building->construction_complete();
	return true;
}

bool	Game::check_new_unit(void)
{
	info_units*			info;
	std::list<Building*>::iterator	it;
	std::list<Building*>::iterator	it_end;

	info = Env::get_instance()->client.get_msg<info_units>();
	if (info == 0)
		return true;
	it = this->__player[info->id_player]->get_buildings()->begin();
	it_end = this->__player[info->id_player]->get_buildings()->end();
	while (it != it_end)
	{
		if ((*it)->get_id() == info->id_building)
			break;
		it++;
	}
	if (it == it_end)
		return false;
	if ((*it)->product(this->__player[info->id_player], info->nb_product, &this->__unit_in_construct) == false)
		return false;
	Env::get_instance()->state.set_unit_in_construct(true);
	Env::get_instance()->client.remove_buffer_read(info->size);
	return true;
}

bool	Game::counter_attack(Unit* unit, int id_player_to_attack)
{
	std::list<Unit*>::iterator	it = this->__player[id_player_to_attack]->get_units()->begin();
	int				x = unit->pos().x - unit->get_portee();
	int				y = unit->pos().y - unit->get_portee();

	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;
	while (it != this->__player[id_player_to_attack]->get_units()->end())
	{
		if ((*it)->pos().x >= x && (*it)->pos().y >= y &&
		    (*it)->pos().x <= unit->get_portee() + unit->pos().x &&
		    (*it)->pos().y <= unit->get_portee() + unit->pos().y)
		{
			unit->is_action(true, (*it));
			break;
		}
		it++;
	}
	return true;
}

bool	Game::make_attack_unit(units_attack* info)
{
	std::list<Unit*>::iterator	it;
	Warrior*			unit = 0;
	bool				ret = true;

	it = this->__player[info->id_player_attacked]->get_units()->begin();
	while (it != this->__player[info->id_player_attacked]->get_units()->end())
	{
		if ((*it)->get_id() == info->id_unit_attacked)
			break;
		it++;
	}
	if (it == this->__player[info->id_player_attacked]->get_units()->end())
		return true;
	unit = new Warrior(".");
	if (info->id_player_attacked == this->__id_mainplayer && (*it)->get_state() != UACTION)
		this->counter_attack(*it, info->id_player_attack);
	ret = unit->action((*it), info->hp_to_remove);
	delete unit;
	if (ret == false)
	{
		this->__container_game->get_map()->set_unit((*it)->pos().x / 32, (*it)->pos().y / 32, 0);
		this->__player[info->id_player_attacked]->erase_unit(*it);
		if (this->__container_game->del_child(*it) == false)
			return false;
		this->__player[info->id_player_attacked]->set_unemployed(-1);
		if (info->id_player_attacked == this->__id_mainplayer || info->id_player_attack == this->__id_mainplayer)
			Env::get_instance()->state.set_attack_unit(false);
	}
	else if (ret == true && info->id_player_attack == this->__id_mainplayer)
		Env::get_instance()->state.set_attack_time(true);
	return true;
}

void	Game::delete_unit_in_product(Building* building)
{
	std::list<Unit*>::iterator	it(this->__unit_in_construct.begin());

	while (it != this->__unit_in_construct.end())
	{
		if ((*it)->get_producer()->get_id() == building->get_id())
			it = this->__unit_in_construct.erase(it);
		else
			it++;
	}
}

bool	Game::make_attack_building(units_attack* info)
{
	std::list<Building*>::iterator	it;
	Warrior*			unit = 0;
	bool				ret = true;

	it = this->__player[info->id_player_attacked]->get_buildings()->begin();
	while (it != this->__player[info->id_player_attacked]->get_buildings()->end())
	{
		if ((*it)->get_id() == info->id_unit_attacked)
			break;
		it++;
	}
	if (it == this->__player[info->id_player_attacked]->get_buildings()->end())
		return true;
	unit = new Warrior(".");
	ret = unit->action(*it, info->hp_to_remove);
	delete unit;
	if (ret == false)
	{
		if ((*it)->get_state() == BACTION)
			this->delete_unit_in_product(*it);
		this->__player[info->id_player_attacked]->erase_building(*it);
		if (this->__container_game->del_child(*it) == false)
			return false;
		if (info->id_player_attack == this->__id_mainplayer)
			Env::get_instance()->state.set_attack_unit(false);
	}
	else if (ret == true && info->id_player_attack == this->__id_mainplayer)
		Env::get_instance()->state.set_attack_time(true);
	return true;
}

bool	Game::check_destroying_opposants(int id_player)
{
	if (this->__player[id_player]->get_units()->size() == 0 &&
	    this->__player[id_player]->get_buildings()->size() == 0)
	{
		this->__nb_player--;
		this->__player[id_player]->set_wood(-this->__player[id_player]->get_wood());
		this->__player[id_player]->set_gold(-this->__player[id_player]->get_gold());
		if (this->__nb_player == 1)
			return false;
	}
	return true;
}

bool	Game::check_attack(void)
{
	units_attack*			info;
	bool				ret = true;

	info = Env::get_instance()->client.get_msg<units_attack>();
	if (info == 0)
		return true;
	if (info->info == IUNIT)
		ret = this->make_attack_unit(info);
	else
		ret = this->make_attack_building(info);
	if (ret == false)
		return false;
	if (this->check_destroying_opposants(info->id_player_attacked) == false)
		Env::get_instance()->client.player_wins(info->id_player_attack);
	Env::get_instance()->client.remove_buffer_read(info->size);
	return true;
}

Player*	Game::get_player(int id)
{
	return this->__player[id];
}

int	Game::get_id_player(void)
{
	return this->__id_mainplayer;
}

bool	Game::check_complete_construction(void)
{
	std::list<Building*>::iterator	it(this->__building_in_construct.begin());

	while (it != this->__building_in_construct.end())
	{
		if ((*it)->is_construction_complete() == true)
		{
			if (this->complete_construction(*it) == false)
				return false;
			it = this->__building_in_construct.erase(it);
		}
		else
			++it;
	}
	if (this->__building_in_construct.empty() == true)
		Env::get_instance()->state.set_building_in_construct(false);
	return true;
}

bool	Game::complete_unit_construction(Unit* unit, int id_player, Point unit_pos)
{
	unit->construction_complete();
	unit->move(unit_pos.x, unit_pos.y);
	if (add_children(this->__container_game, unit) == false || unit->init() == false)
		return false;
	this->__container_game->get_map()->set_unit(unit_pos.x / 32, unit_pos.y / 32, unit);
	unit->init_astar(this->__container_game->get_map());
	this->__player[id_player]->add_units(unit);
	this->__player[id_player]->set_unemployed(1);
	if (this->__id_mainplayer != id_player)
		unit->signals.add(Lib2D::make_func(this->__player[this->__id_mainplayer], &Player::select_unit_to_attack), unit, 0);
	else
		unit->signals.add(Lib2D::make_func(this, &Game::make_inter_unit), unit, 0);

	return true;
}

bool
Game::make_inter_unit(Lib2D::Control* a, void* b)
{
	(void)b;
	Unit*	unit = (Unit*)a;

	if (this->__inter != 0)
		this->del_child(this->__inter);
	this->__interface->set_visible_building(false);
	if (unit->Init_Interface() == false)
		return false;
	this->__inter = unit->Get_Interface();
	this->add_child(this->__inter);
	return true;
}

bool	Game::complete_unit_construction(void)
{
	std::list<Unit*>::iterator	it(this->__unit_in_construct.begin());
	Building*			building = 0;
	Point				unit_pos;

	while (it != this->__unit_in_construct.end())
	{
		building = (*it)->get_producer();
		if ((*it)->is_construction_complete() == true &&
		    this->__container_game->get_map()->get_position_unit(unit_pos, building, *it) == true)
		{
			this->complete_unit_construction(*it, (*it)->get_id_player(), unit_pos);
			it = this->__unit_in_construct.erase(it);
			if (it != this->__unit_in_construct.end() && (*it)->get_producer() == building)
				(*it)->begin_product();
			else if (it == this->__unit_in_construct.end() || (it != this->__unit_in_construct.end() && (*it)->get_producer() != building))
			{
				building->in_sleep();
				building = 0;
			}
		}
		else
			++it;
	}
	if (this->__unit_in_construct.empty() == true)
		Env::get_instance()->state.set_unit_in_construct(false);
	return true;
}

bool	Game::check_move_unit(void)
{
	units_move*	info;

	info = Env::get_instance()->client.get_msg<units_move>();
	if (info == 0)
		return true;
	this->__player[info->id_player]->move_units(info->id_unit, info->pos);
	Env::get_instance()->client.remove_buffer_read(info->size);
	return true;
}

