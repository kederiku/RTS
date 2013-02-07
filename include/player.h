#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "point.h"
#include <list>
#include <vector>
#include <Lib2D.h>

class	Info;
class	Unit;
class	Building;
class	Nation;
class	Map;

class	Player
{
	std::list<Unit*>	__units;
	std::list<Unit*>	__select_units;
	int			__unemployed;
	int			__employed_max;
	std::list<Building*>	__buildings;
	Nation*			__nation;
	bool			__is_player;
	int			__wood;
	int			__gold;
	unsigned int		__id;
	int			__in_product;
public:
	Player(Nation*, int id_player);
	~Player(void);


	void			erase_unit(Unit* units);
	void			set_player(void);
	bool			get_player(void);
	int			get_unemployed(void);
	int			get_employed_max(void);
	void			set_employed_max(int add);
	void			set_unemployed(int add);
	std::list<Unit*>*	get_units(void);
	std::list<Building*>*	get_buildings(void);
	int			get_wood(void);
	int			get_gold(void);
	void			set_wood(int);
	void			set_gold(int);
	void			set_in_product(int);
	int			get_in_product(void);
	unsigned		get_id_player(void);
	Nation*			get_nation(void);
	bool			send_move(const Point& pos, const Map* map);
	bool			move_units(int id_unit, const Point& pos);
	bool			add_building(Building* building);
	bool			add_units(Unit* units);
	void			change_select_units(std::list<Unit*>& units);
	void			erase_building(Building* building);
	void			unselect_unit(void);
	bool			unit_attack(void);
	void			unit_time(void);
	int			check_unit_attacked(std::vector<Info*>* units_to_attack, std::vector<int>* hp_to_remove, Info* unit);
	bool			select_unit_to_attack(Lib2D::Control*, void*);
};

#endif
