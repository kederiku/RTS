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
	BNONE,
	BCONSTRUCT,
	BSLEEP,
	BACTION,
	BDEAD
};

enum	e_type
{
	HOUSE,
	BARRACK,
	TOWER,
	TEMPLE,
	ACADEMY,
	ARCHERY_RANGE,
	STABLE,
	TOWN_CENTER
};

enum	e_unit_state
{
	UNONE,
	UCONSTRUCT,
	USLEEP,
	UMOVE,
	UACTION,
	UDEAD
};

enum	response_type
{
	UNIT_MOVE,
	INFO_PLAYER,
	MSG,
	INFO_GAME,
	LAUNCH_GAME,
	NATION,
	NEW_BUILDING,
	NEW_UNIT,
	UNIT_ATTACK,
	UNKNOW
};

enum	e_ressource
{
	STONE,
	GOLD,
	FOOD,
	WOOD,
	POPU,
	RNONE
};

enum	msg_type
{
	LOGIN,
	LOGOUT,
	WELCOME,
	GAME_FULL,
	GAME_ALREADY_START,
	PLAYER_WIN
};

enum	unit_type
{
	ARCHER,
	DRUIDE,
	KNIGHT,
	MAGE,
	PEON,
	WARRIOR
};

enum	e_sprite
{
	FIELD,
	RESSOURCE
};

enum	e_scrolling
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
	SNONE
};

enum	type_info
{
	IBUILDING,
	IUNIT
};



#endif
