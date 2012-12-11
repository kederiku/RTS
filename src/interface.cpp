#include "interface.h"
#include "ressources.h"
#include "building_interface.h"
#include "building.h"
#include "house.h"
#include "archery_range.h"
#include "farm.h"
#include "stable.h"
#include "barrack.h"
#include "tower.h"
#include "town_center.h"

Interface::Interface()
{
}

bool
Interface::Init()
{
	try
	{
		this->__image_source = new Lib2D::Image;
		this->__img_interface = new Lib2D::Container;
		this->__img_gold = new Lib2D::Container;
		this->__img_wood = new Lib2D::Container;
		this->__img_food = new Lib2D::Container;
		this->__img_stone= new Lib2D::Container;
		this->__img_population= new Lib2D::Container;
	}
	catch(...)
	{
		return false;
	}
	if (Init_Img() == false)
		return false;
	return true;
}

bool
Interface::Make_image(Lib2D::Container* container, int x, int y, int w, int h, int x2, int y2)
{
	Lib2D::Image*	image;

	image = this->__image_source->get_image_part(x, y, w, h);
	if (image == NULL)
		return false;
	image->resize(w, h);
	image->move(x2, y2);
	container->add_child(image);
	return true;
}

bool
Interface::Init_Img(void)
{
	if (this->__image_source->load_bmp(ICON) == false)
		return false;
	if (this->Make_image(this->__img_interface, 750, 0, 150, 800, 750, 0) == false ||
	    this->Make_image(this->__img_food, 900, 0, 34, 34, 10, 10) == false ||
	    this->Make_image(this->__img_wood, 934, 0, 34, 34, 144, 10) == false ||
	    this->Make_image(this->__img_stone, 968, 0, 34, 34, 278, 10) == false ||
	    this->Make_image(this->__img_gold, 1002, 0, 34, 34, 412, 10) == false ||
	    this->Make_image(this->__img_population, 900, 34, 34, 34, 546, 10) == false)
		return false;
	if (Init_Building() == false)
		return false;
	return true;
}

bool	Interface::delete_building(int count)
{
	int	i = 0;
	int	nb = 0;

	while (i <= count)
	{
		nb = this->building[count]->children();
		while (nb > 0)
		{
			this->building[count]->del_child(nb - 1);
			nb--;
		}
		delete this->building[count]->building;
		i++;
	}
	delete [] this->building;
	return false;
}

bool
Interface::Init_Building(void)
{
	int		i = 0;
	int		y = 120;
	int		x[NB_BUILDING] = {375, 425, 275, 275, 275, 475, 275};
	int		y2[NB_BUILDING] = {0, 0, 150, 100, 200, 0, 0};
	const char*	wood[NB_BUILDING] = {"100", "100", "200", "200", "250", "100", "250"};
	const char*	stone[NB_BUILDING] = {"0", "0", "0", "0", "0", "150", "250"};
	int		x1[NB_BUILDING] = {0, 68, 169, 271, 372, 476, 550};
	int		w[NB_BUILDING] = {64, 96, 96, 96, 96, 64, 128};
	int		h[NB_BUILDING] = {77, 70, 98, 95, 92, 105, 136};

	while (i < NB_BUILDING)
	{
		this->building[i] = new (std::nothrow)Building_Inter();
		if (this->building[i] == 0)
			return false;
		this->building[i]->move(760, y);
		if (this->building[i]->init() == false)
			return this->delete_building(i);
		if (this->building[i]->Create_Container(x[i], y2[i], wood[i], stone[i], "0") == false)
			return this->delete_building(i);
		if (i == 0)
			this->building[i]->building = new House("House");
		else if (i == 1)
			this->building[i]->building = new Farm("Farm");
		else if (i == 2)
			this->building[i]->building = new Barrack("Barrack");
		else if (i == 3)
			this->building[i]->building = new Archery_Range("Archery");
		else if (i == 4)
			this->building[i]->building = new Stable("Stable");
		else if (i == 5)
			this->building[i]->building = new Tower("Tower");
		else if (i == 6)
			this->building[i]->building = new Town_Center("Town Center");
		if (this->building[i]->building == 0)
			return this->delete_building(i);
		this->building[i]->building->set_pos(x1[i], 0, w[i], h[i]);
		i++;
		y += 70;
	}
	return true;
}

Lib2D::Container*
Interface::Get_Img(void)
{
	return this->__img_interface;
}

Lib2D::Container*
Interface::Get_Gold_Img(void)
{
	return this->__img_gold;
}

Lib2D::Container*
Interface::Get_Stone_Img(void)
{
	return this->__img_stone;
}

Lib2D::Container*
Interface::Get_Wood_Img(void)
{
	return this->__img_wood;
}

Lib2D::Container*
Interface::Get_Food_Img(void)
{
	return this->__img_food;
}

Lib2D::Container*
Interface::Get_Population_Img(void)
{
	return this->__img_population;
}
