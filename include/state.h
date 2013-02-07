#ifndef __STATE_H__
#define __STATE_H__

class	State
{
	bool	__building_in_construct;
	bool	__unit_in_construct;
	bool	__unit_construct;
	bool	__unit_move;
	bool	__attack_unit;
	bool	__attack_time;

	public:
		State(void);
		~State(void);

	void	set_building_in_construct(bool ret);
	void	set_unit_in_construct(bool ret);
	void	set_unit_construct(bool ret);
	void	set_unit_move(bool ret);
	void	set_attack_unit(bool ret);
	void	set_attack_time(bool ret);

	bool	get_building_in_construct(void);
	bool	get_unit_in_construct(void);
	bool	get_unit_construct(void);
	bool	get_unit_move(void);
	bool	get_attack_unit(void);
	bool	get_attack_time(void);
};

#endif
