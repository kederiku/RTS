#include "state.h"

	State::State(void)
{
	this->__building_in_construct = false;
	this->__unit_in_construct = false;
	this->__unit_construct = false;
	this->__unit_move = false;
	this->__attack_unit = false;
}

	State::~State(void)
{
}

void	State::set_building_in_construct(bool ret)
{
	this->__building_in_construct = ret;
}

void	State::set_unit_in_construct(bool ret)
{
	this->__unit_in_construct = ret;
}

void	State::set_unit_construct(bool ret)
{
	this->__unit_construct = ret;
}

void	State::set_unit_move(bool ret)
{
	this->__unit_move = ret;
}

void	State::set_attack_unit(bool ret)
{
	this->__attack_unit = ret;
}

void	State::set_attack_time(bool ret)
{
	this->__attack_time = ret;
}

bool	State::get_building_in_construct(void)
{
	return this->__building_in_construct;
}

bool	State::get_unit_in_construct(void)
{
	return this->__unit_in_construct;
}

bool	State::get_unit_construct(void)
{
	return this->__unit_construct;
}

bool	State::get_unit_move(void)
{
	return this->__unit_move;
}

bool	State::get_attack_unit(void)
{
	return this->__attack_unit;
}

bool	State::get_attack_time(void)
{
	return this->__attack_time;
}
