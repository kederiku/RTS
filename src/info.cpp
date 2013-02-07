#include "info.h"
#include "ui.h"
#include "ui.hpp"
#include "inter.h"
#include "graphics/graphics.h"

Info::Info(const char* name, int hp, int power, int portee, int build_time, int id_player, type_info info): __player(0), __life(0)
{
	this->__name = name;
	this->__hp = hp;
	this->__hp_max = hp;
	this->__power = power;
	this->__portee = portee;
	this->__build_time = build_time;
	this->__id_player = id_player;
	this->__info = info;
}

Info::~Info(void)
{
	if (this->__life != 0 && this->_parent != 0)
		this->_parent->del_child(this->__life);
}


bool	Info::init(void)
{

	return true;
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

bool		Info::set_hp(int add)
{
	this->__hp += add;
	if (this->__hp <= 0)
		return false;
	this->__life->resize(this->_rect.w * this->__hp / this->__hp_max, 3);
	return true;
}

int	Info::get_id_player(void) const
{
	return this->__id_player;
}

int	Info::get_id(void)
{
	return this->__id;
}

type_info	Info::get_type_info(void)
{
	return this->__info;
}


Player*		Info::get_player(void) const
{
	return this->__player;
}

void		Info::set_player(Player* player)
{
		this->__player = player;
}

bool	Info::derived_treat_render(void)
{
	Lib2D::graphics::draw_rect(0, 0, this->__size_life, 3, this->__color, this->__life->get_surface_ref());
	return true;
}

bool	Info::init_life(void)
{
	if (this->_parent == 0)
		return true;
	if (this->__id_player == 1 || this->__id_player == 0)
		this->__color.r = 255;
	if (this->__id_player == 2 || this->__id_player == 0)
		this->__color.g = 255;
	if (this->__id_player == 3)
		this->__color.b = 255;
	this->__life = new (std::nothrow) Lib2D::Container;
	if (this->__life == 0)
		return false;
	if (add_children(this->_parent, this->__life, false) == false)
		return false;
	this->__life->resize(this->_rect.w, 3);
	this->__life->move(this->_pos.x -10, this->_pos.y -10);
	if (this->__life->init() == false)
		return false;
	this->__size_life = this->_rect.w;
	return true;
}
