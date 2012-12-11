#ifndef __UNIT_H__
#define __UNIT_H__

#include "info.h"
#include "enums.h"


class Unit : public Info
{
	protected:

	int		__distance;
	t_pos*		__destination;
	e_unit_state	__state;
	int		__portee;

	public:
			Unit(const char*, int hp, int power, int portee, int build_time);
	bool		action(void);

	virtual bool	set_hp(int add);
	e_unit_state	get_state(void);
	t_pos*		get_destination(void);
	int		get_distance(void);
	bool		set_distance(int add);
	bool		is_destroyed(void);
};

#endif
