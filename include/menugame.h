#ifndef __MENUGAME_H__
#define __MENUGAME_H__

#include "Lib2D.h"
#include "my_popup.h"
class	Nation;
struct	info_game;

class	Menugame : public Lib2D::Context
{
private:
	std::list<Nation*>	__nations;
	int			__nb_land;
	bool			__is_in_game;
	Lib2D::Popup_m*		__popup;

	bool		create_popup(const char* title);
	bool		del_popup(Lib2D::Control*, void*);
	bool		check_network(void);
	bool		create_game(info_game*);
public:
	Menugame(void);
	virtual ~Menugame(void);
	bool		init_menugame(void);
	bool		choose_nation(Lib2D::Control* control, void* data);
	bool		print_nation(Lib2D::Control* control, void* data);
	virtual bool	derived_treat_render(void);
};

#endif
