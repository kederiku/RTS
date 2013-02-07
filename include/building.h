#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "info.h"
#include "enums.h"
#include "point.h"
#include <Lib2D.h>

class	Unit;

struct	t_infopos
{
	int	x;
	int	y;
	int	w;
	int	h;
};

class	Building : public Info
{
protected:
	e_building_state	__state;
	e_type			__type;
	t_infopos		__posimage;
	t_infopos		__finish_pos;
	Lib2D::Timer		__timer;
	unit_type		__product;

public:
	static unsigned int	nb_building;
				Building(const char*, int hp, int power, int portee, int build_time, int id_player);
	virtual 		~Building(void);

	bool			init(void);
	virtual bool		product(Player* player, int value, std::list<Unit*>* unit_in_construct) = 0;
	virtual bool		set_hp(int add);
	e_building_state	get_state(void);
	void			in_sleep(void);
	bool			is_destroyed(void);
	e_type			get_type(void);
	t_infopos*		get_pos(void);
	void			set_pos(int, int, int, int);
	virtual bool		Init_Interface(Player*) = 0;
	Inter*			Get_Interface(void);
	void			Set_Interface(void);
	void			construction_complete(void);
	bool			is_construction_complete(void);
	unit_type		get_unit_type(void);
	int			get_id_player(void);
	unit_type		get_product(void);
};

#endif
