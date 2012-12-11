#include "stable.h"
#include "ressources.h"

Stable::Stable(const char* name) : Building(name, 2250, 20, 18, 50)
{
	this->__type = STABLE;
}

bool
Stable::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[1];

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
	return this->__inter->Init_Interface(image, this->__name, player, this);
}

bool	Stable::product(Lib2D::Control* control, void* data)
{
	(void)control;
	(void)data;
	return true;
}
