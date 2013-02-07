#ifndef	_RESPONSE_H_
#define _RESPONSE_H_

#include "point.h"
#include "enums.h"

#include <iostream>
struct	info_struct
{
	response_type	type;
	unsigned int	size;
	info_struct(response_type type, unsigned int size = sizeof(info_struct)): type(type), size(size)
	{
	}
};

struct	nation: public info_struct
{
	e_land	id_nation;
	nation(void): info_struct(NATION, sizeof(nation))
	{
	}
};

struct	msg: public info_struct
{
	msg_type	id_msg;
	unsigned	data;
	msg(void): info_struct(MSG, sizeof(msg))
	{
	}
	void	get_msg(char* ret) const;
};

struct	info_building: public info_struct
{
	Point	pos;
	e_type	id_build;
	int	player;
	info_building(void): info_struct(NEW_BUILDING, sizeof(info_building))
	{
	}
};

struct	info_units: public info_struct
{
	int		id_building;
	int		id_player;
	int		nb_product;
	info_units(void): info_struct(NEW_UNIT, sizeof(info_units))
	{
	}
};

struct	info_game: public info_struct
{
	bool			ready;
	char			nb_player;
	unsigned short int	id_player;
	struct
	{
		e_land		nation;
	}	player[8];
	info_game(void): info_struct(INFO_GAME, sizeof(info_struct) + sizeof(ready) + sizeof(nb_player) + sizeof(id_player))
	{
	}
};

struct	info_player: public info_struct
{
	unsigned short int	nb_player;
	char			player[8];
	info_player(int id_player): info_struct(INFO_PLAYER, sizeof(info_struct) + sizeof(nb_player)), nb_player(1)
	{
		*player = id_player;
	}
};

struct	units_move: public info_struct
{
	Point		pos;
	unsigned	id_unit;
	unsigned	id_player;
	units_move(void): info_struct(UNIT_MOVE, sizeof(info_units))
	{
	}
};

struct	units_attack: public info_struct
{
	int		id_unit_attacked;
	int		hp_to_remove;
	int		id_player_attack;
	int		id_player_attacked;
	type_info	info;
	units_attack(void): info_struct(UNIT_ATTACK, sizeof(units_attack))
	{
	}
};

#endif
