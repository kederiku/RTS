#include "building.h"
#include "ressources.h"
#include "env.hpp"
#include "inter.h"

Building::Building(const char* name, int hp, int power, int portee, int build_time, int id_player) : Info(name, hp, power, portee, build_time, id_player, IBUILDING)
{
	this->__state = BNONE;
	this->__inter = 0;
	this->__product = PEON;
	this->__id = -1;
	if (id_player != -1)
	{
		this->__id = nb_building;
		++nb_building;
	}
	this->__timer.start();
}

Building::~Building(void)
{
}

bool	Building::init(void)
{
	if (Env::get_instance()->ressource.init_subimage_building(this, this->__type) == false)
		return false;
	this->resize(this->__finish_pos.w, this->__finish_pos.h);
	if (this->init_life() == false)
		return false;
	return true;
}

bool	Building::set_hp(int add)
{
	if (this->Info::set_hp(add) == false)
	{
		this->__state = BDEAD;
		return false;
	}
	return true;
}

e_building_state	Building::get_state(void)
{
	return this->__state;
}

void			Building::in_sleep(void)
{
	this->__state = BSLEEP;
}

bool	Building::is_destroyed(void)
{
	if (this->__hp > 0)
		return false;
	else
		return true;
}

e_type	Building::get_type(void)
{
	return this->__type;
}

t_infopos*	Building::get_pos(void)
{
	return &this->__posimage;
}

void		Building::set_pos(int x, int y, int w, int h)
{
	this->__posimage.x = x;
	this->__posimage.y = y;
	this->__posimage.w = w;
	this->__posimage.h = h;
}

Inter*
Building::Get_Interface(void)
{
	return this->__inter;
}

void
Building::Set_Interface(void)
{
	this->__inter = 0;
}

void	Building::construction_complete(void)
{
	this->__state = BCONSTRUCT;
	this->_rect.x = this->__finish_pos.x;
	this->_rect.y = this->__finish_pos.y;
	this->_rect.w = this->__finish_pos.w;
	this->_rect.h = this->__finish_pos.h;
}

bool	Building::is_construction_complete(void)
{
	if (this->__timer.get_ticks() < this->__build_time * 1000)
		return false;
	this->__timer.stop();
	return true;
}

unit_type	Building::get_unit_type(void)
{
	return this->__product;
}

int		Building::get_id_player(void)
{
	return this->__id_player;
}

unit_type	Building::get_product(void)
{
	return this->__product;
}
