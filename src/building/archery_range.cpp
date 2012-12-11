#include "archery_range.h"
#include "ressources.h"

Archery_Range::Archery_Range(const char* name) : Building(name, 2250, 0, 0, 50)
{
	this->__type = ARCHERY_RANGE;
}

bool
Archery_Range::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];

	if ((this->__inter = new (std::nothrow)Inter) == 0)
	{
		delete this->__inter;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(275, 100, 50, 50);
	image[1] = img_source.get_image_part(325, 100, 50, 50);
	if (image[0] == 0 || image[1] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this);
}

bool	Archery_Range::product(Lib2D::Control* control, void* data)
{
	(void)control;
	(void)data;
	return true;
}
