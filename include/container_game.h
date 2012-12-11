#ifndef _CONTAINER_GAME_H_
#define _CONTAINER_GAME_H_

#include "point.h"
#include "enums.h"
#include "my_popup.h"
#include "map.h"
#include "control/display/multi/table.h"
#include <iostream>
#include <stdlib.h>
#include <list>

#define WIDTH_GAME	700
#define HEIGHT_GAME	600
#define SIZE_CASE	32
#define NB_CASE_WIDTH	WIDTH_GAME / SIZE_CASE
#define NB_CASE_HEIGHT	HEIGHT_GAME / SIZE_CASE

class	Container_game : public Lib2D::Container
{
	Point			__pos_container_map;
	Lib2D::Image		__sprite_field;
	Lib2D::Image		__sprite_ressource;
	Map			__map;
	unsigned short int	__width;
	unsigned short int	__heigh;

	bool	check_position(const Point& pos, const Point& target);
	bool	new_case(const Point& sprite, const Point& dest);
	bool	load_cases_map(void);
	bool	load_ressource(void);
	bool	init_map(void);
	bool	init_new_map(void);
	bool	refresh_img(void);
	bool	init_container(void);
public:
	Container_game(void);
	virtual ~Container_game(void);

	virtual bool	init(const char* path);
	virtual bool	init(int width, int height);
	bool		derived_treat_event(Lib2D::Event* event);
	bool		add_field(const Point& sprite, const Point& mouse);
	bool		save(const char* file);
	bool		add_sprite(const info_img&, const Point&);
	bool		add_field(const info_img&, const Point& mouse);
	bool		add_ressource(const info_img& info, const Point& mouse);
};

#endif
