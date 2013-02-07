#include "stable.h"
#include "ressources.h"
#include "knight.h"
#include "player.h"
#include "env.hpp"

Stable::Stable(const char* name, int id_player) : Building(name, 2250, 20, 18, 60, id_player)
{
	this->__type = STABLE;
	this->__finish_pos.x = 205;
	this->__finish_pos.y = 264;
	this->__finish_pos.w = 95;
	this->__finish_pos.h = 96;
	this->__product = KNIGHT;
	this->__costs.wood = 100;
	this->__costs.gold = 150;
}

Stable::~Stable(void)
{
}

bool
Stable::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];
	Knight*		knight = new Knight("Knight");

	if ((this->__inter = new (std::nothrow)Inter) == 0)
	{
		delete this->__inter;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(275, 200, 50, 50);
	image[1] = img_source.get_image_part(325, 200, 50, 50);
	if (image[0] == 0 || image[1] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this, knight);
}

bool	Stable::product(Player* player, int value, std::list<Unit*>* unit_in_construct)
{
	Knight*		knights;
	int		i(0);

	this->__state = BACTION;
	while (i < value)
	{
		knights = new (std::nothrow)Knight("Knight", player->get_id_player());
		if (knights == 0)
			return false;
		if (knights->get_costs().wood > player->get_wood() || knights->get_costs().gold > player->get_gold())
		{
			delete knights;
			return true;
		}
		if (knights->init() == false)
		{
			delete knights;
			return false;
		}
		player->set_wood(-knights->get_costs().wood);
		player->set_gold(-knights->get_costs().gold);
		knights->set_producer(this);
		unit_in_construct->push_back(knights);
		if (i == 0)
			knights->begin_product();
		i++;
	}
	return true;
}
