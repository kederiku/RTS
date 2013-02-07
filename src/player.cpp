#include "player.h"
#include "unit.h"
#include "nation.h"
#include "env.hpp"
#include "map.h"

Player::Player(Nation* nation, int id_player)
{
	this->__nation = nation;
	this->__unemployed = 0;
	this->__employed_max = 10;
	this->__gold = 500;
	this->__wood = 500;
	this->__id = id_player;
	this->__in_product = 0;
}

Player::~Player(void)
{
	delete this->__nation;
}

int
Player::get_unemployed(void)
{
	return this->__unemployed;
}

int
Player::get_employed_max(void)
{
	return this->__employed_max;
}

void
Player::set_employed_max(int add)
{
	this->__employed_max += add;
}

int
Player::get_in_product(void)
{
	return this->__in_product;
}

void
Player::set_in_product(int add)
{
	this->__in_product = add;
}

void
Player::set_unemployed(int add)
{
	this->__unemployed += add;
}


std::list<Unit*>*
Player::get_units(void)
{
	return &this->__units;
}

std::list<Building*>*
Player::get_buildings(void)
{
	return &this->__buildings;
}

int
Player::get_wood(void)
{
	return this->__wood;
}

int
Player::get_gold(void)
{
	return this->__gold;
}

unsigned
Player::get_id_player(void)
{
	return this->__id;
}

void
Player::set_wood(int add)
{
	this->__wood += add;
}

void
Player::set_gold(int add)
{
	this->__gold += add;
}

bool	Player::send_move(const Point& pos, const Map*)
{
	std::list<Unit*>::iterator	it(this->__select_units.begin());
	std::list<Unit*>::iterator	it_end(this->__select_units.end());

	while (it != it_end)
	{
		if (Env::get_instance()->client.unit_move(pos, (*it)->get_id(), this->__id) == false)
			return false;
		++it;
	}
	return true;
}

bool	Player::move_units(int id_unit, const Point& pos)
{
	std::list<Unit*>::iterator	it(this->__units.begin());
	std::list<Unit*>::iterator	it_end(this->__units.end());

	while (it != it_end && (*it)->get_id () != id_unit)
		++it;
	if (it != it_end)
		(*it)->set_destination(pos);
	return true;
}

bool	Player::add_building(Building* building)
{
	try
	{
		this->__buildings.push_back(building);
	}
	catch (std::bad_alloc&)
	{
		return false;
	}
	return true;
}

bool	Player::add_units(Unit* units)
{
	try
	{
		this->__units.push_back(units);
	}
	catch (std::bad_alloc&)
	{
		return false;
	}
	return true;
}

Nation*		Player::get_nation(void)
{
	return this->__nation;
}

void		Player::change_select_units(std::list<Unit*>& units)
{
	this->__select_units.swap(units);
}

void		Player::erase_unit(Unit* units)
{
	remove_data_list(this->__units, units);
	remove_data_list(this->__select_units, units);
}

void		Player::erase_building(Building* building)
{
	remove_data_list(this->__buildings, building);
}

void		Player::unselect_unit(void)
{
	this->__select_units.clear();
}

bool	Player::select_unit_to_attack(Lib2D::Control* control, void* data)
{
	Info*				unit = (Info*)control;
	std::list<Unit*>::iterator	it = this->__units.begin();
	int				x;
	int				y;

	while (it != this->__units.end())
	{
		x = (*it)->pos().x - (*it)->get_portee();
		y = (*it)->pos().y - (*it)->get_portee();
		if (x < 0)
			x *= -1;
		else if (x == 0)
			continue;
		if (y < 0)
			y *= -1;
		else if (y == 0)
			continue;
		if ((*it)->get_type() != PEON)
		{
			if (unit->pos().x >= x && unit->pos().y >= y &&
			    unit->pos().x <= (*it)->get_portee() + (*it)->pos().x &&
			    unit->pos().y <= (*it)->get_portee() + (*it)->pos().y)
				(*it)->is_action(true, unit);
		}
		it++;
	}
	(void)data;
	return true;
}

void
Player::unit_time(void)
{
	std::list<Unit*>::iterator	it = this->__units.begin();
	int				i = 0;

	while (it != this->__units.end())
	{
		if ((*it)->get_state() == UACTION)
		{
			if ((*it)->is_attack_complete() == true)
			{
				if ((*it)->get_unit_to_attack()->get_hp() < 0)
					(*it)->is_action(false);
				else
					Env::get_instance()->state.set_attack_unit(true);
			}
			else
				i++;
		}
		it++;
	}
	if (i == 0)
		Env::get_instance()->state.set_attack_time(false);
}

int
Player::check_unit_attacked(std::vector<Info*>* units_to_attack, std::vector<int>* hp_to_remove, Info* unit)
{
	unsigned int	ret = 0;

	while (ret < units_to_attack->size())
	{
		if ((*units_to_attack)[ret] == unit)
			return ret;
		ret++;
	}
	if (ret == units_to_attack->size())
	{
		units_to_attack->push_back(unit);
		hp_to_remove->push_back(0);
	}
	return ret;
}

bool
Player::unit_attack(void)
{
	std::list<Unit*>::iterator	it = this->__units.begin();
	std::vector<Info*>		units_to_attack;
	std::vector<int>		hp_to_remove;
	unsigned int			i = 0;
	int				x;
	int				y;

	while (it != this->__units.end())
	{
		if ((*it)->get_state() == UACTION)
		{
			x = (*it)->pos().x - (*it)->get_portee();
			y = (*it)->pos().y - (*it)->get_portee();
			if (x < 0)
				x *= -1;
			else if (x == 0)
				continue;
			if (y < 0)
				y *= -1;
			else if (y == 0)
				continue;
			if ((*it)->get_unit_to_attack()->pos().x >= x && (*it)->get_unit_to_attack()->pos().y >= y &&
			    (*it)->get_unit_to_attack()->pos().x <= (*it)->get_portee() + (*it)->pos().x &&
			    (*it)->get_unit_to_attack()->pos().y <= (*it)->get_portee() + (*it)->pos().y)
			{
				i = this->check_unit_attacked(&units_to_attack, &hp_to_remove, (*it)->get_unit_to_attack());
				hp_to_remove[i] += (*it)->get_power();
				(*it)->begin_attack();
			}
			else
			{
				(*it)->is_action(false);
				Env::get_instance()->state.set_attack_unit(false);
			}
		}
		it++;
	}
	i = 0;
	while (i < units_to_attack.size())
	{
		if (Env::get_instance()->client.unit_attack(this->__id, units_to_attack[i]->get_id_player(), units_to_attack[i]->get_id(), hp_to_remove[i], units_to_attack[i]->get_type_info()) == false)
			return false;
		Env::get_instance()->state.set_attack_unit(false);
		i++;
	}
	return true;
}

