#include "nation.h"
#include "ressource.h"
#include "env.hpp"

Nation::Nation(void)
{
	this->__image = 0;
	this->is_select = false;
}

bool			Nation::init_nation(e_land land, t_pos pos)
{
	Lib2D::Subimage*	image(NULL);

	try
	{
		this->__image = new Lib2D::Container;
		image = new Lib2D::Subimage;
	}
	catch(...)
	{
		delete this->__image;
		delete image;
		return false;
	}
	this->__land = land;
	this->__image->resize(200, 300);
	this->__image->move(pos.x, pos.y);
	if (this->__image->init() == false ||
	    Env::get_instance()->ressource.init_subimage_flags(image, this->__land) == false || this->__image->add_child(image) == false)
	{
		delete this->__image;
		delete image;
		return false;
	}
	image->move(0, 0);
	return true;
}

Lib2D::Container*	Nation::get_container(void)
{
	return this->__image;
}

e_land			Nation::get_land(void)
{
	return this->__land;
}
