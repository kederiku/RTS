#include "town_center.h"
#include "player.h"
#include "ressources.h"
#include "peon.h"
#include "env.hpp"

Town_Center::Town_Center(const char* name, int id_player) : Building(name, 5000, 0, 0, 90, id_player)
{
	this->__type = TOWN_CENTER;
	this->__finish_pos.x = 270;
	this->__finish_pos.y = 17;
	this->__finish_pos.w = 119;
	this->__finish_pos.h = 104;
	this->__costs.wood = 250;
	this->__costs.gold = 250;
}

Town_Center::~Town_Center(void)
{
}

bool
Town_Center::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];
	Peon*		peon = new Peon("Peon");

	if ((this->__inter = new (std::nothrow)Inter) == 0 || peon == 0)
	{
		delete this->__inter;
		delete peon;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(275, 0, 50, 50);
	image[1] = img_source.get_image_part(325, 0, 50, 50);
	if (image[0] == 0 || image[1] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this, peon);
}

bool	delete_unit(Peon** peons, int i)
{
	while (i > -1)
	{
		delete peons[i];
		i--;
	}
	return false;
}

bool	Town_Center::product(Player* player, int value, std::list<Unit*>* unit_in_construct)
{
	Peon*		peons;
	int		i = 0;

	this->__state = BACTION;
	while (i < value)
	{
		peons = new (std::nothrow) Peon("Peon", player->get_id_player());
		if (peons == 0)
			return false;
		if (peons->get_costs().wood > player->get_wood() || peons->get_costs().gold > player->get_gold())
		{
			delete peons;
			return true;
		}
		if (peons->init() == false)
		{
			delete peons;
			return false;
		}
		player->set_wood(-peons->get_costs().wood);
		player->set_gold(-peons->get_costs().gold);
		peons->set_producer(this);
		peons->set_player(player);
		unit_in_construct->push_back(peons);
		if (i == 0)
			peons->begin_product();
		i++;
	}
	return true;
}
