#ifndef __INFO_H__
#define __INFO_H__

struct	t_cost
{
	int	gold;
	int	wood;
	int	population;
};

#include "enums.h"
#include "point.h"
#include "control/display/multi/container.h"
#include "control/display/object/subimage.h"

#include "control/display/color.h"

class	Player;
class	Inter;

class	Info: public Lib2D::Subimage
{
protected:
	type_info		__info;
	int			__hp;
	int			__hp_max;
	int			__power;
	int			__portee;
	unsigned		__build_time;
	const char*		__name;
	t_cost			__costs;
	int			__id_player;
	int			__id;
	Player*			__player;
	Point			__iconpoint;
	Inter*			__inter;
	Lib2D::Container*	__life;
	int			__size_life;
	Lib2D::Color		__color;

	bool		init_life(void);
public:
			Info(const char* name, int hp, int power, int portee, int build_time, int id_player, type_info info);
	virtual		~Info(void);

	virtual bool	init(void);
	int		get_build_time(void);
	int		get_hp(void);
	int		get_hp_max(void);
	int		get_power(void);
	int		get_portee(void);
	const char*	get_name(void);
	t_cost		get_costs(void);
	virtual bool	set_hp(int add);
	int		get_id(void);
	int		get_id_player(void) const;
	type_info	get_type_info(void);
	Player*		get_player(void) const;
	void		set_player(Player* player);
	bool		derived_treat_render(void);
};

#endif
