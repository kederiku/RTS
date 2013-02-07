#ifndef __UNIT_H__
#define __UNIT_H__

#include "position.h"
#include "info.h"
#include "enums.h"
#include "astar.h"
#include "building.h"
#include <Lib2D.h>
#include <list>
#include <stack>
class	Map;

class Unit : public Info
{
	enum	unit_animation
	{
		TOP,
		BOTTOM,
		RIGHT,
		LEFT,
		TOP_RIGHT,
		TOP_LEFT,
		BOTTOM_RIGHT,
		BOTTOM_LEFT
	};
protected:
	struct	ptr_fct
	{
		int (Unit::*fct)(void);
	};
	Point			__destination;
	Point			__next_case;
	e_unit_state		__state;
	int			__portee;
	unit_type		__type;
	astar			__astar;
	Lib2D::Timer		__timer;
	bool			__is_constructed;
	std::list<Point>	__path;
	Building*		__producer;
	Map*			__map;
	std::stack<ptr_fct>	__order;
	Info*			__unit_to_attack;
	unit_animation		__frame;
	int			__id_frame;
	int			__sprite_animation;
	int 			(Unit::*__action)(void);

	int			search_path(void);
	int			set_next_case(void);
	int			move_to_dest(void);
	void			change_animation(const position& pos);
	void			set_animation(unit_animation anim);
	void			set_frame(int frame);
	void			stop_animation(void);
	bool			add_order(int (Unit::*fct)(void));
public:
	static unsigned int	nb_unit;
				Unit(const char*, int hp, int power, int portee, int build_time, int id_player = -1);

	virtual bool		set_hp(int add);
	bool			init(void);
	void			init_astar(Map* map);
	virtual bool		action(Info*, int);
	e_unit_state		get_state(void);
	Point*			get_destination(void);
	virtual bool		set_destination(const Point& dest);
	bool			is_destroyed(void);
	void			begin_product(void);
	void			construction_complete(void);
	bool			is_construction_complete(void);
	unit_type		get_type(void);
	int			get_id_player(void);
	void			set_producer(Building*);
	Building*		get_producer(void);
	virtual bool		derived_treat_render(void);
	virtual void		move(int32_t x, int32_t y);
	void			is_action(bool, Info* unit = 0);
	Info*			get_unit_to_attack(void);
	void			begin_attack(void);
	bool			is_attack_complete(void);
	virtual int		get_ressource(void);
	virtual int		search_ressource(void);
	virtual int		back_town_center(void);
	virtual int		drop_ressource(void);
	Inter*			Get_Interface(void);
	void			Set_Interface(void);
	bool			Init_Interface(void);
};

#endif
