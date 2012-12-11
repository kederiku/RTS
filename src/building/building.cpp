#include "building.h"

Building::Building(const char* name, int hp, int power, int portee, int build_time) : Info(name, hp, power, portee, build_time)
{
	this->__state = BNONE;
	this->__inter = 0;
}

bool	Building::action(void)
{
	return true;
}

bool	Building::set_hp(int add)
{
	this->__hp += add; //si on est attaque on envoie -nbdehpenleve, a l'inverse +hpgagne
	if (this->__hp <= 0)
	{
		this->__state = BDEAD;
		return false; //ici on meurt *rage*
	}
	return true;
}

e_building_state	Building::get_state(void)
{
	return this->__state;
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

bool
Building::Init_Interface(Player* player)
{
	(void)player;
	return true;
}

bool		Building::product(Lib2D::Control* control, void* data)
{
	(void)control;
	(void)data;
	std::cout << "Building\n";
	return true;
}
