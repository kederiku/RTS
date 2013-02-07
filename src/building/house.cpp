#include "house.h"
#include "ressources.h"
#include "player.h"

House::House(const char* name, int id_player) : Building(name, 750, 0, 0, 30, id_player)
{
	this->__type = HOUSE;
	this->__finish_pos.x = 398;
	this->__finish_pos.y = 4;
	this->__finish_pos.w = 64;
	this->__finish_pos.h = 64;
	this->__costs.wood = 100;
	this->__costs.gold = 0;
}

House::~House(void)
{
}

bool
House::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];

	if ((this->__inter = new (std::nothrow)Inter) == 0)
	{
		delete this->__inter;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(375, 0, 50, 50);
	image[1] = NULL;
	if (image[0] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this, 0);
}

bool	House::product(Player* player, int value, std::list<Unit*>* unit_in_construct)
{
	(void)value;
	(void)unit_in_construct;
	player->set_employed_max(10);
	return true;
}
