#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <list>

class	Unit;
class	Building;
class	Nation;

class	Player
{
	std::list<Unit*>	__units;
	int			__unemployed;
	std::list<Building*>	__buildings;
	Nation*			__nation;
	bool			__is_player;
	public:
				Player(Nation*);
				~Player(void);
	void			set_player(void);
	bool			get_player(void);
	int			get_unemployed(void);
	void			set_unemployed(int add);
};

#endif
