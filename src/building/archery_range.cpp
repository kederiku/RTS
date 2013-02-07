#include "archery_range.h"
#include "ressources.h"
#include "archer.h"
#include "player.h"
#include "env.hpp"

Archery_Range::Archery_Range(const char* name, int id_player) : Building(name, 2250, 0, 0, 60, id_player)
{
	this->__type = ARCHERY_RANGE;
	this->__finish_pos.x = 521;
	this->__finish_pos.y = 303;
	this->__finish_pos.w = 96;
	this->__finish_pos.h = 94;
	this->__product = ARCHER;
	this->__costs.wood = 250;
	this->__costs.gold = 0;
}

Archery_Range::~Archery_Range(void)
{
}

bool
Archery_Range::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];
	Archer*		archer = new Archer("Archer");

	if ((this->__inter = new (std::nothrow)Inter) == 0 || archer == 0)
	{
		delete this->__inter;
		delete archer;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(275, 100, 50, 50);
	image[1] = img_source.get_image_part(325, 100, 50, 50);
	if (image[0] == 0 || image[1] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this, archer);
}

bool	Archery_Range::product(Player* player, int value, std::list<Unit*>* unit_in_construct)
{
	Archer*		archers;
	int		i = 0;

	this->__state = BACTION;
	while (i < value)
	{
		archers = new (std::nothrow)Archer("Archer", get_id_player());
		if (archers == 0)
			return false;
		if (archers->get_costs().wood > player->get_wood() || archers->get_costs().gold > player->get_gold())
		{
			delete archers;
			return true;
		}
		if (archers->init() == false)
		{
			delete archers;
			return false;
		}
		player->set_wood(-archers->get_costs().wood);
		player->set_gold(-archers->get_costs().gold);
		archers->set_producer(this);
		unit_in_construct->push_back(archers);
		if (i == 0)
			archers->begin_product();
		i++;
	}
	return true;
}
