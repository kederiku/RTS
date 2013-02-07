#ifndef	_S_RESSOURCES_H_
#define _S_RESSOURCES_H_

#include "enums.h"
#include "control/display/object/subimage.h"
#include "control/display/multi.h"
#include "env.hpp"
#include "map.h"
#include "inter.h"

class	Ressources: public Lib2D::Subimage
{
	e_ressource	__type;
	int		__capacity;
	int		__capacity_max;
	Lib2D::Multi*	__parent;
	Map*		__map;
	Inter*		__inter;

public:
	Ressources(void);
	virtual ~Ressources(void);

	bool		init(e_ressource type, int capacity, Lib2D::Multi* parent, Map* map);
	e_ressource	get_type(void) const;
	int		get_capacity(void) const;
	int		get_capacity_max(void) const;
	int		take(int nb);
	bool		Init_Interface();
	Inter*		Get_Interface(void);
	void		Set_Interface(void);
	void		delete_inter(void);
};

#endif
