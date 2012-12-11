#include "info.h"

Info::Info(const char* name, int hp, int power, int portee, int build_time)
{
	this->__name = name;
	this->__hp = hp;
	this->__hp_max = hp;
	this->__power = power;
	this->__actualpos = 0;
	this->__portee = portee;
	this->__build_time = build_time;
}

int		Info::get_build_time(void)
{
	return this->__build_time;
}

int		Info::get_hp(void)
{
	return this->__hp;
}

int		Info::get_hp_max(void)
{
	return this->__hp_max;
}

t_pos*		Info::get_actual_pos(void)
{
	return this->__actualpos;
}

int		Info::get_power(void)
{
	return this->__power;
}

const char*	Info::get_name(void)
{
	return this->__name;
}

t_cost		Info::get_costs(void)
{
	return this->__costs;
}

int		Info::get_portee(void)
{
	return this->__portee;
}
