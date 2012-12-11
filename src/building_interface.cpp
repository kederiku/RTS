#include "building_interface.h"
#include "ressources.h"

Building_Inter::Building_Inter(): Container(), __label_wood(NULL), __label_stone(NULL), __label_gold(NULL)
{
}

Building_Inter::~Building_Inter()
{
}

bool
Building_Inter::Create_Container(int x, int y, const char* wood, const char* stone, const char* gold)
{
	Lib2D::Image	image;
	Lib2D::Image*	tmp;

	if (image.load_bmp(ICON) == false)
		return false;
	this->resize(60, 150);
	tmp = image.get_image_part(x, y, 50, 50);
	if (tmp == 0)
		return false;
	if (this->add_child(tmp) == false)
	{
		delete tmp;
		return false;
	}
	if (this->Add_Img(image) == false)
		return false;
	if (this->Add_Label(wood, stone, gold) == false)
		return false;
	return true;
}



bool
Building_Inter::Add_Img(Lib2D::Image& image)
{
	unsigned	i(0);
	Lib2D::Image*	tmp;

	while (i < 3)
	{
		tmp = image.get_image_part(1050 + i * 20, 0, 20, 20);
		if (tmp == 0)
			return false;
		tmp->resize(20, 20);
		tmp->move(55, i * 20);
		if (this->add_child(tmp) == false)
		{
			delete tmp;
			return false;
		}
		++i;
	}
	return true;
}

bool
Building_Inter::Add_Label(const char* wood, const char* stone, const char* gold)
{
	try
	{
		this->__label_wood = new Lib2D::Label;
		this->__label_stone = new Lib2D::Label;
		this->__label_gold = new Lib2D::Label;
	}
	catch(...)
	{
		delete this->__label_wood;
		delete this->__label_stone;
		delete this->__label_gold;
		return false;
	}
	this->__label_wood->move(80, 0);
	this->__label_stone->move(80, 20);
	this->__label_gold->move(80, 40);

	if (this->__label_wood->init(wood, FONT, 20, 0XCECECEFF, false) == false)
		return false;
	if (this->__label_stone->init(stone, FONT, 20, 0XCECECEFF, false) == false)
		return false;
	if (this->__label_gold->init(gold, FONT, 20, 0XCECECEFF, false) == false)
		return false;
	if (this->add_child(this->__label_wood) == false)
	{
		delete this->__label_wood;
		return false;
	}
	if (this->add_child(this->__label_stone) == false)
	{
		delete this->__label_stone;
		return false;
	}
	if (this->add_child(this->__label_gold) == false)
	{
		delete this->__label_gold;
		return false;
	}
	return true;
}
