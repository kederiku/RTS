#include "farm.h"
#include "ressources.h"

Farm::Farm(const char* name) : Building(name, 375, 0, 0, 20)
{
	this->__type = FARM;
}

bool
Farm::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];

	if ((this->__inter = new (std::nothrow)Inter) == 0)
	{
		delete this->__inter;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(425, 0, 50, 50);
	image[1] = NULL;
	if (image[0] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this);
}

bool	Farm::product(Lib2D::Control* control, void* data)
{
	(void)control;
	(void)data;
	return true;
}
