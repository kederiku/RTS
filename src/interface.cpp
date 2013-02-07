#include "interface.h"
#include "ressources.h"
#include "building_interface.h"
#include "building.h"
#include "house.h"
#include "archery_range.h"
#include "stable.h"
#include "barrack.h"
#include "tower.h"
#include "town_center.h"
#include "control/display/object/subimage.h"
#include "game.h"
#include "ns_var.h"
#include "player.h"
#include "tools.h"
#include "temple.h"
#include "academy.h"
#include "ui.h"
#include "ui.hpp"

Interface::Interface()
{
	unsigned	i(0);

	while (i < NB_BUILDING)
	{
		this->__building[i] = 0;
		++i;
	}
}

Interface::~Interface()
{
	unsigned	i(0);

	while (i < NB_BUILDING)
	{
		delete this->__building[i];
		++i;
	}
}

bool	Interface::make_image(Game* game, int x, int y, int w, int h, int x2, int y2)
{
	Lib2D::Subimage*	img(0);

	img = new (std::nothrow) Lib2D::Subimage;
	if (img == 0 || img->init(&this->__image_source, x, y, w, h) == false || game->add_child(img) == false)
	{
		delete img;
		return false;
	}
	img->move(x2, y2);
	return true;
}

bool		Interface::init(Game* game, e_land nation)
{
	if (this->__image_source.load_bmp(ICON) == false)
		return false;
	this->__label_wood = create_label("0", 50, 15, 30, 0XCECECEFF);
	if (add_children(game, this->__label_wood) == false)
		return false;
	this->__label_gold = create_label("0", 184, 15, 30, 0XCECECEFF);
	if (add_children(game, this->__label_gold) == false)
		return false;
	this->__label_popu = create_label("0", 586, 15, 30, 0XCECECEFF);
	if (add_children(game, this->__label_popu) == false)
		return false;
	if (this->make_image(game, 736, 0, 164, 800, 736, 0) == false ||
	    this->make_image(game, 934, 0, 34, 34, 10, 10) == false ||
	    this->make_image(game, 1002, 0, 34, 34, 144, 10) == false ||
	    this->make_image(game, 900, 34, 34, 34, 546, 10) == false)
		return false;
	if (this->init_nation_interface(game, nation)  == false)
		return false;
	return true;
}

bool
Interface::init_nation_interface(Game* game, e_land nation)
{
	e_type	type_building[NB_BUILDING] = {HOUSE, BARRACK, TOWER, ARCHERY_RANGE, STABLE, TOWN_CENTER};

	switch (nation)
	{
		case ENGLAND:
			type_building[1] = TEMPLE;
			break;
		case FRANCE:
			break;
		case GERMANY:
			type_building[3] = ACADEMY;
			break;
		case JAPAN:
			type_building[4] = ACADEMY;
			break;
		case USA:
			type_building[3] = TEMPLE;
			break;
		case OTHER:
			return false;
	}
	return this->init_building(game, type_building);
}

bool
Interface::init_building(Game* game, e_type* type_building)
{
	int		i = 0;
	int		y = 120;
	const char*	wood[NB_BUILDING] = {"100", "200", "200", "250", "100", "250"};
	const char*	gold[NB_BUILDING] = {"0", "0", "0", "0", "150", "250"};

	while (i < NB_BUILDING)
	{
		this->__build[i] = new (std::nothrow)Building_Inter();
		if (this->__build[i] == 0 || this->__build[i]->init() == false ||
		   this->__build[i]->Create_Container(wood[i], gold[i]) == false ||
		    game->add_child(this->__build[i]) == false)
		{
			delete this->__build[i];
			return false;
		}
		if (this->__build[i]->set_building(type_building[i]) == false)
			return false;
		switch (type_building[i])
		{
			case ACADEMY:
				this->__building[i] = new (std::nothrow) Academy("Academy");
				break;
			case ARCHERY_RANGE:
				this->__building[i] = new (std::nothrow) Archery_Range("Archery");
				break;
			case BARRACK:
				this->__building[i] = new (std::nothrow) Barrack("Barrack");
				break;
			case HOUSE:
				this->__building[i] = new (std::nothrow) House("House");
				break;
			case STABLE:
				this->__building[i] = new (std::nothrow) Stable("Stable");
				break;
			case TEMPLE:
				this->__building[i] = new (std::nothrow) Temple("Temple");
				break;
			case TOWER:
				this->__building[i] = new (std::nothrow) Tower("Tower");
				break;
			case TOWN_CENTER:
				this->__building[i] = new (std::nothrow) Town_Center("Town Center");
				break;
		}
		if (this->__building[i] == 0 || this->__building[i]->init() == false)
			return false;
		if (this->__build[i]->signals.add(Lib2D::make_func(game, &Game::Create_Building), 0, this->__building[i]) == false)
			return false;
		this->__build[i]->move(760, y);
		i++;
		y += 70;
	}
	return true;
}

void	Interface::set_visible_building(bool visible)
{
	unsigned	i(0);

	while (i < NB_BUILDING)
	{
		this->__build[i]->visible(visible);
		++i;
	}
}


bool
Interface::check_ressource(Player* player)
{
	int		nb = player->get_employed_max() - player->get_unemployed();
	char		buffer[25];
	unsigned	str_len;

	id::itoa(player->get_wood(), buffer);
	if (this->__label_wood->set_label(buffer) == false)
		return false;
	id::itoa(player->get_gold(), buffer);
	if (this->__label_gold->set_label(buffer) == false)
		return false;
	id::itoa(player->get_employed_max() - nb, buffer);
	str_len = ns_cmc::ns_var::f_str_len(buffer);
	buffer[str_len] = '/';
	id::itoa(player->get_employed_max(), buffer + str_len + 1);
	if (this->__label_popu->set_label(buffer) == false)
		return false;
	return true;
}
