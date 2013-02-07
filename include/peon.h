#ifndef __PEON_H__
#define __PEON_H__

#include "unit.h"
#include "control/timer.h"
class	Ressources;

class	Peon : public Unit
{
	Point		__closest_ressource;
	e_ressource	__ressource;
	int		__nb_ressource;
	Lib2D::Timer	__ressource_time;

	int		search_other_ressource(void);
public:
	Peon(const char* name, int id_player = -1);

	virtual bool	set_destination(const Point& dest);
	virtual int	get_ressource(void);
	virtual int	search_ressource(void);
	virtual int	back_town_center(void);
	virtual int	drop_ressource(void);
};

#endif
