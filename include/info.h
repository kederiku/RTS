#ifndef __INFO_H__
#define __INFO_H__

struct	t_cost
{
	int	food;
	int	stone;
	int	gold;
	int	wood;
	int	population;
};

struct	t_pos;

class	Info
{
	protected:

		int		__hp;
		int		__hp_max;
		int		__power;
		int		__portee;
		int		__build_time;
		const char*	__name;
		t_pos*		__actualpos;
		t_cost		__costs;

	public:

				Info(const char* name, int hp, int power, int portee, int build_time);
		int		get_build_time(void);
		int		get_hp(void);
		int		get_hp_max(void);
		virtual bool	set_hp(int add)=0;
		t_pos*		get_actual_pos(void);
		int		get_power(void);
		int		get_portee(void);
		const char*	get_name(void);
		t_cost		get_costs(void);
};

#endif
