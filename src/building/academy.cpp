#include "academy.h"
#include "ressources.h"
#include "mage.h"
#include "player.h"
#include "env.hpp"

Academy::Academy(const char* name, int id_player) : Building(name, 2250, 20, 18, 60, id_player)
{
	this->__type = ACADEMY;
	this->__finish_pos.x = 0;
	this->__finish_pos.y = 657;
	this->__finish_pos.w = 96;
	this->__finish_pos.h = 96;
	this->__product = MAGE;
	this->__costs.wood = 250;
	this->__costs.gold = 150;
}

Academy::~Academy(void)
{
}

bool
Academy::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];
	Mage*		mage = new Mage("Mage");

	if (img_source.load_bmp(ICON) == false || (this->__inter = new (std::nothrow)Inter) == 0 || mage == 0)
	{
		delete mage;
		delete this->__inter;
		return false;
	}
	image[0] = img_source.get_image_part(275, 50, 50, 50);
	image[1] = img_source.get_image_part(325, 50, 50, 50);
	if (image[0] == 0 || image[1] == 0)
	{
		delete mage;
		delete this->__inter;
		return false;
	}
	return this->__inter->Init_Interface(image, this->__name, player, this, mage);
}

bool	Academy::product(Player* player, int value, std::list<Unit*>* unit_in_construct)
{
	Mage*		mages;
	int		i(0);

	this->__state = BACTION;
	while (i < value)
	{
		mages = new (std::nothrow)Mage("Mage", player->get_id_player());
		if (mages == 0)
			return false;
		if (mages->get_costs().wood > player->get_wood() || mages->get_costs().gold > player->get_gold())
		{
			delete mages;
			return true;
		}
		if (mages->init() == false)
		{
			delete mages;
			return false;
		}
		player->set_wood(-mages->get_costs().wood);
		player->set_gold(-mages->get_costs().gold);
		mages->set_producer(this);
		unit_in_construct->push_back(mages);
		if (i == 0)
			mages->begin_product();
		i++;
	}
	return true;
}
