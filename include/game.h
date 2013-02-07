#ifndef __GAME_H__
#define __GAME_H__

#include "map_editor.h"
#include <Lib2D.h>
#include "control/display/object/subimage.h"
#include "state.h"
#include "response.h"

class	Player;
class	Nation;
class	Interface;
class	Inter;
class	Container_game;
class	Building;
class	Unit;
class	Info;
class	Menugame;

class	Game : public Lib2D::Container
{
	Inter*			__inter;
	Building*		__building;

	bool			__is_select;
	int			__id_mainplayer;
	Map_editor		__map;
	bool			__init;
	Nation*			__nation;
	std::vector<Player*>	__player;
	Interface*		__interface;
	Lib2D::Subimage*	__new_building;
	Container_game*		__container_game;
	e_type			__building_type;
	std::list<Building*>	__building_in_construct;
	std::list<Unit*>	__unit_in_construct;
	int			__nb_player;

	void			del_interface_building(void);
	bool			is_in_container_map(const Lib2D::s_mouse_event* mouse_event) const;
	bool			check_new_building(void);
	bool			complete_construction(Building* building);
	bool			complete_unit_construction(void);
	bool			complete_unit_construction(Unit* unit, int id_player, Point unit_pos);
	bool			check_new_unit(void);
	bool			check_complete_construction(void);
	bool			check_attack(void);
	bool			move_new_building(const Lib2D::s_mouse_event* mouse_event);
	void			move_units(const Point& mouse_event);
	bool			check_move_unit(void);
	bool			init_towncenter(void);
	bool			create_towncenter(int i, const Point& pos);
	bool			select_units(const Point& mouse);
	bool			check_destroying_opposants(int id_player);
public:
				Game(void);
	virtual			~Game(void);
	bool			Init_game(Player** player, int id_mainplayer);
	virtual bool		derived_treat_render(void);
	virtual bool		derived_treat_event(Lib2D::Event* event);
	bool			Create_Building(Lib2D::Control* a, void* b);
	bool			Build(Lib2D::Control* a, void* b);
	Player*			get_player(int);
	int			get_id_player(void);
	bool			make_inter_unit(Lib2D::Control*, void*);
	bool			inter_ressources(Lib2D::Control*, void*);
	bool			counter_attack(Unit* unit, int id_player_to_attack);
	bool			make_attack_unit(units_attack* info);
	bool			make_attack_building(units_attack* info);
	void			delete_unit_in_product(Building* building);
	void			delete_inter(void);
};

#endif
