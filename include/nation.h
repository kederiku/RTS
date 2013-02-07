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
	e_land			__land;
	Lib2D::Container*	__image;

	public:
				Nation(void);
	bool			is_select;
	bool			init_nation(e_land land, t_pos pos);
	Lib2D::Container*	get_container(void);
	e_land			get_land(void);
};

#endif
