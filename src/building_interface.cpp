#include "building_interface.h"
#include "ressources.h"
#include "env.hpp"
#include "control/display/object/subimage.h"

Building_Inter::Building_Inter(): Container(), __label_wood(NULL), __label_gold(NULL)
{
}

Building_Inter::~Building_Inter()
{
}

bool
Building_Inter::Create_Container(const char* wood,  const char* gold)
{
	this->resize(60, 150);
	if (this->Add_Img(WOOD, 0) == false || this->Add_Img(GOLD, 20) == false)
		return false;
	if (this->Add_Label(wood, gold) == false)
		return false;
	return true;
}

bool
Building_Inter::Add_Img(e_ressource type, int y)
{
	Lib2D::Subimage*	image;

	image = new (std::nothrow) Lib2D::Subimage;
	if (image == 0 ||
	    Env::get_instance()->ressource.init_subimage_icon_ressource(image, type) == false ||
	    this->add_child(image) == false)
	{
		delete image;
		return false;
	}
	image->move(55, y);
	return true;
}

bool
Building_Inter::Add_Label(const char* wood, const char* gold)
{
	try
	{
		this->__label_wood = new Lib2D::Label;
		this->__label_gold = new Lib2D::Label;
	}
	catch(...)
	{
		delete this->__label_wood;
		delete this->__label_gold;
		return false;
	}
	if (this->add_child(this->__label_wood) == false)
	{
		delete this->__label_wood;
		delete this->__label_gold;
		return false;
	}
	if (this->add_child(this->__label_gold) == false)
	{
		delete this->__label_gold;
		this->del_child(this->__label_wood);
		return false;
	}
	this->__label_wood->move(80, 0);
	this->__label_gold->move(80, 20);
	if (this->__label_wood->init(wood, FONT, 20, 0XCECECEFF, false) == false)
		return false;
	if (this->__label_gold->init(gold, FONT, 20, 0XCECECEFF, false) == false)
		return false;
	return true;
}

bool	Building_Inter::set_building(e_type type)
{
	Lib2D::Subimage*	image;

	image = new (std::nothrow) Lib2D::Subimage;

	if (image == 0 ||
	    Env::get_instance()->ressource.init_subimage_icon_building(image, type) == false ||
	    this->add_child(image) == false)
	{
		delete image;
		return false;
	}
	return true;
}
