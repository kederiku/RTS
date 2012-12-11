#ifndef	_RESPONSE_H_
#define _RESPONSE_H_

#include "point.h"
#include "enums.h"

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

struct	info_game: public info_struct
{
	bool	ready;
	char	nb_player;
	struct
	{
		e_land	nation;
		Point	pos;
	}	player[8];
	info_game(void): info_struct(INFO_GAME, sizeof(info_game))
	{
	}
};

#endif
