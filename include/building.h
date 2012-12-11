#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "info.h"
#include "enums.h"
#include "point.h"
#include "inter.h"
#include <Lib2D.h>

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
	Inter*			__inter;
	bool			__is_constructed;


public:
				Building(const char*, int hp, int power, int portee, int build_time);
	bool			action(void);
	virtual bool		set_hp(int add);
	e_building_state	get_state(void);
	bool			is_destroyed(void);
	e_type			get_type(void);
	t_infopos*		get_pos(void);
	void			set_pos(int, int, int, int);
	virtual bool		Init_Interface(Player*);
	Inter*			Get_Interface(void);
	void			Set_Interface(void);
	virtual bool		product(Lib2D::Control*, void* data);
};

#endif
