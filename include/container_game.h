#ifndef _CONTAINER_GAME_H_
#define _CONTAINER_GAME_H_

#include "interface.h"
#include "point.h"
#include "enums.h"
#include "my_popup.h"
#include "map.h"
#include "control/display/multi/table.h"
#include <iostream>
#include <stdlib.h>
#include <list>
class	Game;
class	Units;

class	Container_game : public Lib2D::Container
{
	struct
	{
		int	x;
		int	y;
	}			__pos;
	e_scrolling		__scrolling;
	Lib2D::Image		__sprite_ressource;
	Map			__map;
	int			__width;
	int			__heigh;
	Lib2D::Blitable*	__blitable;
	bool			__units;
	Point			__select_units;

//	bool	check_position(const Point& pos, const Point& target);
	bool	new_case(const Point& sprite, const Point& dest);
	bool	load_cases_map(void);
	bool	load_ressource(void);
	bool	load_building(void);
	bool	init_map(void);
	bool	init_new_map(void);
	bool	refresh_img(void);
	bool	init_container(int width, int height);
	bool	new_ressource(e_ressource type, const Point& dest);
	bool	create_building(void);
public:
	Container_game(void);
	virtual ~Container_game(void);

	virtual bool	init(const char* path, int width = 750, int height = 800);
	virtual bool	init(int nb_case_width, int nb_case_heigh, int width = 750, int height = 800);
//	virtual bool	treat_event(Lib2D::Event* event);
//	virtual bool	treat_render(void);
	virtual bool	derived_treat_event(Lib2D::Event* event);
	virtual bool	derived_treat_render(void);
	bool		add_field(const Point& sprite, const Point& mouse);
	bool		save(const char* file);
	bool		add_building(Lib2D::Control* ctrl, e_type building_type, int id_player);
	bool		create_building(const Point& mouse, Building* building);
	bool		check_pos_construction(Lib2D::Control* ctrl) const;
	bool		add_ressource(e_ressource ressource, const Point& mouse);
	Map*		get_map(void);
	void		get_pos(const Point& mouse, Point* ret);
	void		select(const Point& mouse);

	void		debug_collision(void);
	bool		select_units(const Point& mouse, std::list<Unit*>& units, int id_player);
	bool		multi_select(const Point& end, std::list<Unit*>& units, int id_player);
	bool		selection(const Point& begin, const Point& end, int x, int y, std::list<Unit*>& units, int id_player);
	bool		add_units(unsigned x, unsigned y, std::list<Unit*>& units, int id_player);
	void		move_map(const Point& center);
};

#endif
