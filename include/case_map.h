#ifndef	_CASE_MAP_H_
#define _CASE_MAP_H_

#include "control.h"
#include "point.h"
class	Building;
class	Unit;
class	Ressources;

class	Case_map
{
	bool	check_collision(const Point& origin_pos, const Point& origin_size, const Point& target_pos, const Point& target_size) const;
	bool	check_collision(const Point& origin_pos, const Point& origin_size, Lib2D::Control* target) const;
public:
	Point		pos_image;
	bool		collision;
	Ressources*	ressource;
	Building*	building;
	Unit*		unit;

	Case_map(void);
	bool			search_collision(void) const;
	bool			search_collision(const Point& pos, Lib2D::Control* unit) const;

};

#endif
