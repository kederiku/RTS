#include "tower.h"
#include "ressources.h"

Tower::Tower(const char* name) : Building(name, 700, 20, 18, 50)
{
	this->__type = TOWER;
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
	return this->__inter->Init_Interface(image, this->__name, player, this);
}

bool	Tower::product(Lib2D::Control* control, void* data)
{
	(void)control;
	(void)data;
	return true;
}
