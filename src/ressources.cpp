#include "s_ressources.h"

Ressources::Ressources(void)
{
	this->__inter = 0;
}

Ressources::~Ressources(void)
{
}

bool	Ressources::init(e_ressource type, int capacity, Lib2D::Multi* parent, Map* map)
{
	this->__type = type;
	this->__capacity_max = capacity;
	this->__capacity = capacity;
	this->__parent = parent;
	this->__map = map;
	if (Env::get_instance()->ressource.init_subimage_ressource(this, this->__type) == false)
		return false;
	return true;
}

e_ressource	Ressources::get_type(void) const
{
		return this->__type;
}

int		Ressources::get_capacity(void) const
{
		return this->__capacity;
}

int		Ressources::get_capacity_max(void) const
{
		return this->__capacity_max;
}


int	Ressources::take(int nb)
{
	int	ret(this->__capacity);

	if (this->__capacity > nb)
	{
		this->__capacity -= nb;
		return nb;
	}
	else
	{
		this->__map->set_case_ressource(Point(this->_pos.x, this->_pos.y), Point(this->_pos.w, this->_pos.h), 0);
		this->__capacity = 0;
		this->__parent->del_child(this);
		return ret;
	}
}

Inter*
Ressources::Get_Interface(void)
{
	return this->__inter;
}

void
Ressources::Set_Interface(void)
{
	this->__inter = 0;
}

bool
Ressources::Init_Interface(void)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image = 0;
	const char*	name = 0;

	if (img_source.load_bmp(ICON) == false || (this->__inter = new (std::nothrow)Inter)== 0)
		return false;
	if (this->__type == WOOD)
	{
		name = "Wood";
		image = img_source.get_image_part(934, 0, 34, 34);
	}
	else if (this->__type == GOLD)
	{
		name = "Gold";
		image = img_source.get_image_part(1002, 0, 34, 34);
	}
	if (image == 0)
	{
		delete this->__inter;
		return false;
	}
	return this->__inter->Head_Inter_Ressource(image, name, this);
}
