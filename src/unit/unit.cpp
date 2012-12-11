#include "unit.h"

Unit::Unit(const char* name, int hp, int power, int portee, int build_time) : Info(name, hp, power, portee, build_time)
{
	this->__state = NONE;
	this->__destination = 0;
	this->__distance = -1;
}

bool	Unit::action(void)
{
	return true;
}

bool	Unit::set_hp(int add)
{
	this->__hp += add; //si on est attaque on envoie -nbdehpenleve, a l'inverse +hpgagne
	if (this->__hp <= 0)
	{
		this->__state = DEAD;
		return false; //ici on meurt *rage*
	}
	return true;
}

e_unit_state	Unit::get_state(void)
{
	return this->__state;
}

t_pos*	Unit::get_destination(void)
{
	return this->__destination;
}

int	Unit::get_distance(void)
{
	return this->__distance;
}

bool	Unit::set_distance(int add)
{
	this->__distance += add;
	if (this->__distance <= 0)
	{
		//changer e_state
		this->__state = SLEEP;
		return true; //on est arrive a destination
	}
	return false;
}

bool	Unit::is_destroyed(void)
{
	if (this->__hp > 0)
		return false;
	else
		return true;
}
