#ifndef _RESSOURCE_H_
#define _RESSOURCE_H_

#include "enums.h"
#include "point.h"
#include "control/display/object/image.h"
#include "control/display/object/subimage.h"

struct	info_ressource
{
	unsigned	x;
	unsigned	y;
	unsigned	w;
	unsigned	h;
};

class	Ressource
{
	Lib2D::Image	__sprite_field;
	Lib2D::Image	__sprite_ressource;
	Lib2D::Image	__sprite_building;
	Lib2D::Image	__sprite_units;
	Lib2D::Image	__sprite_flags;
	Lib2D::Image	__sprite_icon;
public:
	bool	init(void);
	bool	get_info_building(info_ressource* ret, e_type type);
	bool	init_subimage_building(Lib2D::Subimage* init, e_type type);
	bool	get_info_icon_building(info_ressource* ret, e_type type);
	bool	init_subimage_icon_building(Lib2D::Subimage* init, e_type type);
	bool	get_info_units(info_ressource* ret, unit_type type);
	bool	init_subimage_units(Lib2D::Subimage* init, unit_type type);
	bool	get_info_icon_ressource(info_ressource* ret, e_ressource type);
	bool	init_subimage_icon_ressource(Lib2D::Subimage* init, e_ressource type);
	bool	get_info_ressource(info_ressource* ret, e_ressource type);
	bool	init_subimage_ressource(Lib2D::Subimage* init, e_ressource type);
	bool	get_info_flags(info_ressource* ret, e_land type);
	bool	init_subimage_flags(Lib2D::Subimage* init, e_land type);
	bool	init_subimage_sprite_field(Lib2D::Subimage* init, const Point& pos, int size);
};

#endif
