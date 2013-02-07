#include "ressource.h"
#include "ressources.h"

bool	Ressource::init(void)
{
	if (this->__sprite_field.load_bmp(MAP) == false ||
	    this->__sprite_field.set_transparence(0, 255, 0) == false)
		return false;
	if (this->__sprite_ressource.load_bmp(RES) == false ||
	    this->__sprite_ressource.set_transparence(0, 255, 0) == false)
		return false;
	if (this->__sprite_building.load_bmp(BUILD) == false ||
	    this->__sprite_building.set_transparence(0, 255, 0) == false)
		return false;
	if (this->__sprite_units.load_bmp(UNIT) == false ||
	    this->__sprite_units.set_transparence(0, 255, 0) == false)
		return false;
	if (this->__sprite_icon.load_bmp(ICON) == false ||
	    this->__sprite_icon.set_transparence(0, 255, 0) == false)
		return false;
	if (this->__sprite_flags.load_bmp(FLAGS) == false ||
	    this->__sprite_flags.set_transparence(0, 255, 0) == false)
		return false;
	return true;
}

bool	Ressource::get_info_building(info_ressource* ret, e_type type)
{
	switch (type)
	{
		case ACADEMY :
			ret->x = 0;
			ret->y = 753;
			ret->w = 91;
			ret->h = 86;
			return true;
		case ARCHERY_RANGE:
			ret->x = 521;
			ret->y = 400;
			ret->w = 89;
			ret->h = 93;
			return true;
		case BARRACK :
			ret->x = 307;
			ret->y = 569;
			ret->w = 96;
			ret->h = 81;
			return true;
		case HOUSE :
			ret->x = 398;
			ret->y = 73;
			ret->w = 63;
			ret->h = 59;
			return true;
		case STABLE :
			ret->x = 206;
			ret->y = 360;
			ret->w = 93;
			ret->h = 96;
			return true;
		case TEMPLE :
			ret->x = 96;
			ret->y = 742;
			ret->w = 95;
			ret->h = 70;
			return true;
		case TOWER :
			ret->x = 401;
			ret->y = 199;
			ret->w = 60;
			ret->h = 63;
			return true;
		case TOWN_CENTER :
			ret->x = 270;
			ret->y = 157;
			ret->w = 111;
			ret->h = 95;
			return true;
		default :
			return false;
	}
	return false;
}

bool	Ressource::init_subimage_building(Lib2D::Subimage* init, e_type type)
{
	info_ressource	info;

	if (this->get_info_building(&info, type)  == false)
		return false;
	if (init == 0 || init->init(&this->__sprite_building, info.x, info.y, info.w, info.h) == false)
		return false;
	return true;
}

bool	Ressource::get_info_icon_building(info_ressource* ret, e_type type)
{
	ret->w = 50;
	ret->h = 50;
	switch (type)
	{
		case ACADEMY :
			ret->x = 275;
			ret->y = 50;
			return true;
		case ARCHERY_RANGE :
			ret->x = 275;
			ret->y = 100;
			return true;
		case BARRACK :
			ret->x = 275;
			ret->y = 150;
			return true;
		case HOUSE :
			ret->x = 375;
			ret->y = 0;
			return true;
		case STABLE :
			ret->x = 275;
			ret->y = 200;
			return true;
		case TEMPLE :
			ret->x = 275;
			ret->y = 650;
			return true;
		case TOWER :
			ret->x = 475;
			ret->y = 0;
			return true;
		case TOWN_CENTER :
			ret->x = 275;
			ret->y = 0;
			return true;
		default :
			return false;
	}
	return false;
}

bool	Ressource::init_subimage_icon_building(Lib2D::Subimage* init, e_type type)
{
	info_ressource	info;

	if (this->get_info_icon_building(&info, type)  == false)
		return false;
	if (init == 0 || init->init(&this->__sprite_icon, info.x, info.y, info.w, info.h) == false)
		return false;
	init->resize(5, 5);
	return true;
}

bool	Ressource::get_info_units(info_ressource* ret, unit_type type)
{
	switch (type)
	{
		case ARCHER :
			ret->x = 220;
			ret->y = 1145;
			ret->w = 55;
			ret->h = 55;
			break;
		case DRUIDE :
			ret->x = 220;
			ret->y = 2035;
			ret->w = 55;
			ret->h = 55;
			break;
		case KNIGHT :
			ret->x = 256;
			ret->y = 625;
			ret->w = 64;
			ret->h = 64;
			break;
		case MAGE :
			ret->x = 220;
			ret->y = 1590;
			ret->w = 55;
			ret->h = 55;
			break;
		case PEON :
			ret->x = 128;
			ret->y = 0;
			ret->w = 32;
			ret->h = 32;
			break;
		case WARRIOR :
			ret->x = 180;
			ret->y = 260;
			ret->w = 45;
			ret->h = 45;
			break;
		default :
			return false;
	}
	return true;
}

bool	Ressource::init_subimage_units(Lib2D::Subimage* init, unit_type type)
{
	info_ressource	info;

	if (this->get_info_units(&info, type)  == false)
		return false;
	if (init == 0 || init->init(&this->__sprite_units, info.x, info.y, info.w, info.h) == false)
		return false;
	return true;

}


bool	Ressource::get_info_icon_ressource(info_ressource* ret, e_ressource type)
{
	ret->w = 20;
	ret->h = 20;
	ret->y = 0;
	switch (type)
	{
		case STONE:
			ret->x = 1050;
			return true;
		case GOLD :
			ret->x = 1090;
			return true;
		case FOOD :
			ret->x = 1070;
			return true;
		case WOOD :
			ret->x = 1050;
			return true;
		case RNONE :
			ret->x = 1130;
			return true;
		case POPU :
			ret->x = 1130;
			return true;
		default :
			return false;
	}
	return false;
}

bool	Ressource::init_subimage_icon_ressource(Lib2D::Subimage* init, e_ressource type)
{
	info_ressource	info;

	if (this->get_info_icon_ressource(&info, type)  == false)
		return false;
	if (init == 0 || init->init(&this->__sprite_icon, info.x, info.y, info.w, info.h) == false)
		return false;
	return true;
}

bool	Ressource::get_info_ressource(info_ressource* ret, e_ressource type)
{
	ret->y = 0;
	ret->w = 64;
	switch (type)
	{
		case STONE:
			ret->x = 128;
			ret->h = 64;
			return true;
		case GOLD :
			ret->x = 64;
			ret->h = 64;
			return true;
		case FOOD :
			ret->x = 1070;
			ret->h = 20;
			return true;
		case WOOD :
			ret->x = 0;
			ret->h = 128;
			return true;
		case RNONE :
			ret->x = 1130;
			ret->h = 20;
			return true;
		case POPU :
			ret->x = 1130;
			ret->h = 20;
			return true;
		default :
			return false;
	}
	return false;
}

bool	Ressource::init_subimage_ressource(Lib2D::Subimage* init, e_ressource type)
{
	info_ressource	info;

	if (this->get_info_ressource(&info, type)  == false)
		return false;
	if (init == 0 || init->init(&this->__sprite_ressource, info.x, info.y, info.w, info.h) == false)
		return false;
	return true;
}

bool	Ressource::get_info_flags(info_ressource* ret, e_land type)
{
	ret->y = 0;
	ret->w = 200;
	ret->h = 300;
	switch (type)
	{
		case ENGLAND :
			ret->x = 0;
			return true;
		case FRANCE :
			ret->x = 200;
			return true;
		case GERMANY :
			ret->x = 400;
			return true;
		case JAPAN :
			ret->x = 600;
			return true;
		case USA :
			ret->x = 800;
			return true;
		default :
			return false;
	}
	return false;
}

bool	Ressource::init_subimage_flags(Lib2D::Subimage* init, e_land type)
{
	info_ressource	info;

	if (this->get_info_flags(&info, type)  == false)
		return false;
	if (init == 0 || init->init(&this->__sprite_flags, info.x, info.y, info.w, info.h) == false)
		return false;
	return true;
}
bool	Ressource::init_subimage_sprite_field(Lib2D::Subimage* sub, const Point& pos, int size)
{
	if (sub == 0 || sub->init(&this->__sprite_field, pos.x, pos.y, size, size) == false)
		return false;
	return true;
}
