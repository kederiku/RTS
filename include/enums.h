#ifndef _ENUMS_H_
#define _ENUMS_H_

enum	e_land
{
	ENGLAND,
	FRANCE,
	GERMANY,
	JAPAN,
	USA,
	OTHER
};


enum	e_building_state
{
	BSLEEP,
	BACTION,
	BPRODUCT,
	BDEAD,
	BNONE
};

enum	e_type
{
	HOUSE,
	FARM,
	BARRACK,
	TOWER,
	ARCHERY_RANGE,
	STABLE,
	TOWN_CENTER
};

enum	e_unit_state
{
	SLEEP,
	MOVE,
	ACTION,
	DEAD,
	NONE
};

enum	response_type
{
	MSG,
	INFO_GAME,
	LAUNCH_GAME,
	NATION,
	UNKNOW
};

enum	e_ressource
{
	STONE,
	GOLD,
	FOOD,
	WOOD,
	RNONE
};

enum	msg_type
{
	GAME_FULL,
	GAME_ALREADY_START,
	PLAYER_LEFT,
	PLAYER_WIN
};

#endif
