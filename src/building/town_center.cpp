#include "town_center.h"
#include "player.h"
#include "my_popup.h"
#include "ressources.h"

Town_Center::Town_Center(const char* name) : Building(name, 5000, 0, 0, 120)
{
	this->__type = TOWN_CENTER;
}

bool
Town_Center::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];

	if ((this->__inter = new (std::nothrow)Inter) == 0)
		return false;
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(275, 0, 50, 50);
	image[1] = img_source.get_image_part(325, 0, 50, 50);
	if (image[0] == 0 || image[1] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this);
}

bool	Town_Center::product(Lib2D::Control* control, void* data)
{
//	Player*	player = (Player*)data;
	(void)control;
	(void)data;

	std::cout << "Towncenter\n";
	return true;
}
