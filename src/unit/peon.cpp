#include "peon.h"
#include "map.h"
#include "s_ressources.h"
#include "player.h"

Peon::Peon(const char* name, int id_player) : Unit(name, 125, 0, 0, 20, id_player), __ressource(RNONE), __nb_ressource(0)
{
	this->__costs.gold = 0;
	this->__costs.wood = 0;
	this->__costs.population = 1;
	this->__type = PEON;
	this->__iconpoint.x = 325;
	this->__iconpoint.y = 0;
}

bool	Peon::set_destination(const Point& dest)
{
	if (this->__map->get_ressource(dest.x / 32, dest.y / 32) != 0)
	{
		this->__action = &Unit::get_ressource;
		this->__closest_ressource = dest;
	}
	else
	{
		this->__action = 0;
		this->__ressource = RNONE;
	}
	return this->Unit::set_destination(dest);
}

int	Peon::get_ressource(void)
{
	this->__ressource_time.start();
	if (this->add_order(&Unit::search_ressource) == false)
		return -1;
	return 0;
}

int	Peon::search_other_ressource(void)
{
	if (this->__map->get_closest_ressource(Point(this->_pos.x / 32, this->_pos.y / 32),
					       this->__closest_ressource, this->__ressource) == false)
	{
		this->__ressource = RNONE;
		if (this->__nb_ressource > 0)
			return this->back_town_center();
		return this->__order.size();
	}
	this->__closest_ressource *= 32;
	if (this->set_destination(this->__closest_ressource) == false)
		return -1;
	return 0;
}

int	Peon::search_ressource(void)
{
	Ressources*	ressource(this->__map->get_ressource(this->__closest_ressource.x / 32, this->__closest_ressource.y / 32));
	Point		actual_pos(this->_pos.x / 32, this->_pos.y / 32);
	e_ressource	type_ressource;

	if (this->__nb_ressource == 10)
		return this->back_town_center();
	if (actual_pos.is_next_to(this->__closest_ressource / 32) == false || ressource == 0 || ressource->get_capacity() == 0)
		return this->search_other_ressource();
	if (this->__ressource_time.get_ticks() < 1000)
		return 0;
	type_ressource = ressource->get_type();
	if (this->__ressource != type_ressource)
		this->__nb_ressource = 0;
	this->__ressource = type_ressource;
	this->__nb_ressource += ressource->take(1);
	if (this->__nb_ressource == 10)
		return this->back_town_center();
	this->__ressource_time.start();
	return 0;
}

int	Peon::back_town_center(void)
{
	Point	actual_pos(this->_pos.x / 32, this->_pos.y / 32);
	Point	town_pos(actual_pos);

	if (this->__map->get_closest_towncenter(actual_pos, town_pos, this->__id_player) == false)
		return this->__order.size();
	this->Unit::set_destination(Point(town_pos.x * 32, town_pos.y * 32));
	this->__action = &Unit::drop_ressource;
	return 0;
}

int	Peon::drop_ressource(void)
{
	switch (this->__ressource)
	{
		case GOLD:
			this->__player->set_gold(this->__nb_ressource);
			break;
		case WOOD:
			this->__player->set_wood(this->__nb_ressource);
			break;
		default :
			break;
	}
	this->__nb_ressource = 0;
	this->__action = &Unit::get_ressource;
	if (this->__ressource != RNONE && this->Unit::set_destination(this->__closest_ressource) == false)
		return -1;
	return 0;
}
