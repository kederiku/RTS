#include "case_map.h"
#include "building.h"
#include "s_ressources.h"
#include "unit.h"

Case_map::Case_map(void): collision(0), ressource(0), building(0), unit(0)
{
}

bool	Case_map::check_collision(const Point& origin_pos, const Point& origin_size, const Point& target_pos, const Point& target_size) const
{
	if ((target_pos.x >= origin_pos.x + origin_size.x) ||
	    (target_pos.x + target_size.x <= origin_pos.x) ||
	    (target_pos.y >= origin_pos.y + origin_size.y) ||
	    (target_pos.y + target_size.y <= origin_pos.y))
		return false;
	return true;
}

bool	Case_map::check_collision(const Point& origin_pos, const Point& origin_size, Lib2D::Control* target) const
{
	Point	target_pos(target->pos().x, target->pos().y);
	Point	target_size(target->pos().w, target->pos().h);

	return this->check_collision(origin_pos, origin_size, target_pos, target_size);
}

bool	Case_map::search_collision(void) const
{
	if (this->collision == true)
		return true;
	if (this->ressource != 0 || this->building != 0 || this->unit != 0)
		return true;
	return false;
}

bool	Case_map::search_collision(const Point& pos, Lib2D::Control* unit) const
{
	Point	size(unit->pos().w, unit->pos().h);

	if (this->collision == true)
		return true;
	if (this->unit != 0)
	{
		if (this->unit == unit)
			return false;
		if (this->check_collision(pos, size, this->unit) == true)
			return true;
	}
	if (this->ressource != 0 && this->check_collision(pos, size, this->ressource) == true)
		return true;
	if (this->building != 0 && this->check_collision(pos, size, this->building) == true)
		return true;
	return false;
}
