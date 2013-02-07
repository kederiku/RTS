#include "tower.h"
#include "ressources.h"

Tower::Tower(const char* name, int id_player) : Building(name, 700, 20, 18, 60, id_player)
{
	this->__type = TOWER;
	this->__finish_pos.x = 401;
	this->__finish_pos.y = 135;
	this->__finish_pos.w = 58;
	this->__finish_pos.h = 63;
	this->__costs.wood = 200;
	this->__costs.gold = 0;
}

Tower::~Tower(void)
{
}

bool
Tower::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];

	if ((this->__inter = new (std::nothrow)Inter) == 0)
	{
		delete this->__inter;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(475, 0, 50, 50);
	image[1] = NULL;
	if (image[0] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this, 0);
}

bool	Tower::product(Player* player, int value, std::list<Unit*>* unit_in_construct)
{
	(void)player;
	(void)value;
	(void)unit_in_construct;
	return true;
}
