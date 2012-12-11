#ifndef __GAME_H__
#define __GAME_H__

#include "map_editor.h"
#include <Lib2D.h>

class	Player;
class	Nation;
class	Interface;
class	Inter;
class	Container_game;
class	Building;

class	Game : public Lib2D::Container
{
	Inter*			__inter;
	Building*		__building;

	Map_editor		__map;
	bool			__init;
	Nation*			__nation;
	std::list<Player*>	__player;
	Interface*		__interface;
	Lib2D::Container*	__new_building;
	bool			__is_visible;
	Container_game*		__container_game;

	bool	is_in_container_map(const Lib2D::s_mouse_event* mouse_event) const;
public:
	Game(void);
	virtual ~Game(void);

	bool			Init_game(Player** player);
	virtual bool		derived_treat_event(Lib2D::Event* event);
	bool			Create_Building(Lib2D::Control* a, void* b);
	bool			Build(Lib2D::Control* a, void* b);
};

#endif
