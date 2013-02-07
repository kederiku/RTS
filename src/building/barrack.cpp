#include "barrack.h"
#include "ressources.h"
#include "player.h"
#include "warrior.h"
#include "env.hpp"

Barrack::Barrack(const char* name, int id_player) : Building(name, 2250, 0, 0, 60, id_player)
{
	this->__type = BARRACK;
	this->__finish_pos.x = 307;
	this->__finish_pos.y = 458;
	this->__finish_pos.w = 96;
	this->__finish_pos.h = 95;
	this->__product = WARRIOR;
	this->__costs.wood = 200;
	this->__costs.gold = 0;
}

Barrack::~Barrack(void)
{
}

bool
Barrack::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];
	Warrior*	warrior = new Warrior("Warrior");

	if ((this->__inter = new (std::nothrow)Inter) == 0 || warrior == 0)
	{
		delete this->__inter;
		delete warrior;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(275, 150, 50, 50);
	image[1] = img_source.get_image_part(425, 150, 50, 50);
	if (image[0] == 0 || image[1] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this, warrior);
}

bool	Barrack::product(Player* player, int value, std::list<Unit*>* unit_in_construct)
{
	Warrior*	warriors;
	int		i = 0;

	this->__state = BACTION;
	while (i < value)
	{
		warriors = new (std::nothrow)Warrior("Warrior", get_id_player());
		if (warriors == 0)
			return false;
		if (warriors->get_costs().wood > player->get_wood() || warriors->get_costs().gold > player->get_gold())
		{
			delete warriors;
			return true;
		}
		if (warriors->init() == false)
		{
			delete warriors;
			return false;
		}
		player->set_wood(-warriors->get_costs().wood);
		player->set_gold(-warriors->get_costs().gold);
		warriors->set_producer(this);
		unit_in_construct->push_back(warriors);
		if (i == 0)
			warriors->begin_product();
		i++;
	}
	return true;
}
