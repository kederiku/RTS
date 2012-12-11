#ifndef __NATION__
#define __NATION__

#include <list>
#include "Lib2D.h"
#include "enums.h"

class	Unit;

struct	t_pos
{
	int	x;
	int	y;
};

class	Nation
{
	private:
	std::list<Unit*>	__units;
	e_land			__land;
	Lib2D::Container*	__image;

	public:
				Nation(void);
	bool			is_select;
	bool			init_nation(e_land land, t_pos pos);
	Lib2D::Container*	get_container(void);
	e_land			get_land(void);
	Lib2D::Image*		del_unit(Lib2D::Image*, Unit*, Unit*, Unit*);
	Lib2D::Image*		set_england(void);
	Lib2D::Image*		set_france(void);
	Lib2D::Image*		set_japan(void);
	Lib2D::Image*		set_germany(void);
	Lib2D::Image*		set_usa(void);
};

#endif
