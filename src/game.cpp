#include "game.h"
#include "player.h"
#include "interface.h"
#include "building_interface.h"
#include "building.h"
#include "ressources.h"
#include "container_game.h"
#include "ui.hpp"

Game::Game(void): __inter(0), __building(0), __new_building(0), __is_visible(false)
{
}

Game::~Game(void)
{
}

bool
Game::Init_game(Player** player)
{
	int i = 0;

	try
	{
		this->__interface = new Interface;
		while (player[i] != 0)
		{
			this->__player.push_back(player[i]);
			i++;
		}
	}
	catch(...)
	{
		return false;
	}
	i = 0;
	this->resize(900, 800);
	this->move(0, 0);
	if (Container::init() == false || this->__interface->Init() == false)
	{
		delete this->__interface;
		return false;
	}
	this->add_child(this->__interface->Get_Img());
	this->add_child(this->__interface->Get_Food_Img());
	this->add_child(this->__interface->Get_Wood_Img());
	this->add_child(this->__interface->Get_Stone_Img());
	this->add_child(this->__interface->Get_Gold_Img());
	this->add_child(this->__interface->Get_Population_Img());
	while (i < 7)
	{
		this->add_child(this->__interface->building[i]);
		if (this->__interface->building[i]->signals.add(Lib2D::make_func(this, &Game::Create_Building), 0, this->__interface->building[i]->building) == false)
			return false;
		i++;
	}
	this->__container_game = new (std::nothrow) Container_game;
	if (this->__container_game == 0)
		return false;
	if (this->__container_game->init("200") == 0 || add_children(this, this->__container_game) == false)
		return false;
	this->__container_game->move(0, 70);
	return true;
}

bool	Game::is_in_container_map(const Lib2D::s_mouse_event* mouse_event) const
{
	return (mouse_event->x + this->__new_building->pos().w < this->__container_game->pos().w &&
		mouse_event->y + this->__new_building->pos().h < this->__container_game->pos().h  + 70 &&
		mouse_event->x > 0 &&
		mouse_event->y > 70);
}

bool
Game::derived_treat_event(Lib2D::Event* event)
{
	const Lib2D::s_mouse_event*	mouse_event;

	if (this->__new_building == 0)
		return true;
	if (this->__inter != 0 && this->__inter->launch_product == true)
	{
		this->__inter->launch_product = false;
		return this->__building->product(0, 0);
	}
	if (event->get_type() == Lib2D::E_MOUSEMOTION_EVENT)
	{
		if (this->__is_visible == false)
			return true;
//			return true;
		mouse_event = ((Lib2D::Mouse_event*)event)->get_mouse_event();
		if (this->is_in_container_map(mouse_event))
		{
			this->__new_building->move(mouse_event->x, mouse_event->y);
			this->__new_building->visible(true);
		}
		else
			this->__new_building->visible(false);
	}
	else if (event->get_type() == Lib2D::E_MOUSEDOWN_EVENT)
	{
		mouse_event = ((Lib2D::Mouse_event*)event)->get_mouse_event();
		if (this->is_in_container_map(mouse_event) == false)
			return true;
		if (this->__is_visible == false)
		{
			if (mouse_event->button == Lib2D::E_BUTTON_RIGHT)
			{
				if (this->__inter != 0)
				{
					this->__inter->Delete_Interface();
					this->__inter->clean();
					this->del_child(this->__inter);
					this->__inter = 0;
				}
				for (int i =0; i < 7; i++)
					this->__interface->building[i]->visible(true);
			}
		}
		else
		{
			this->__new_building->move(mouse_event->x, mouse_event->y);
			this->__is_visible = false;
		}
	}
	return true;
}

bool	Game::Create_Building(Lib2D::Control*, void* b)
{
	Lib2D::Image		img_source;
	Lib2D::Image*		build = 0;
	Building*		building = (Building*)b;

	if (img_source.load_bmp(BUILD) == false)
		return false;
	build = img_source.get_image_part(building->get_pos()->x, building->get_pos()->y,
					  building->get_pos()->w, building->get_pos()->h);
	if (build == 0)
		return false;
	build->set_transparence(0, 255, 0);
	this->__new_building = new (std::nothrow)Lib2D::Container;
	if (this->__new_building == 0 || add_children(this->__new_building, build) == false)
	{
		delete this->__new_building;
		return false;
	}
	this->__new_building->move(0, 0);
	this->__new_building->resize(building->get_pos()->w, building->get_pos()->h);
	if (add_children(this, this->__new_building) == false || this->__new_building->init() == false ||
	//    this->__new_building->signals.add(Lib2D::make_func(building, &Building::product), 0, 0) == false ||
	    this->__new_building->signals.add(Lib2D::make_func(this, &Game::Build), 0, building) == false)
		return false;
	this->__is_visible = true;
	this->__new_building->visible(false);
	return true;
}

bool
Game::Build(Lib2D::Control* a, void* b)
{
	(void) a;
	Building*	building = (Building*)b;
	int i = 0;

	if (building->Get_Interface() || this->__inter != 0)
	{
		building->Set_Interface();
		return false;
	}
	while (i < 7)
	{
		this->__interface->building[i]->visible(false);
		i++;
	}
	if (building->Init_Interface(this->__player.back()) == false)
		return false;
	this->add_child(building->Get_Interface());
	this->__inter = building->Get_Interface();
	this->__building = building;
	return true;
}
