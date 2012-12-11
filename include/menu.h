#ifndef __MENU_H__
#define __MENU_H__

#include <Lib2D.h>
class	Connection;

class Menu
{
private:
	Connection*		__connection;
	Lib2D::Image*		__background;
	Lib2D::Context*		__context;
	Lib2D::Label*		__title;
	Lib2D::Label_link*	__create;
	Lib2D::Label_link*	__join;
	Lib2D::Context*		__context_play;

	bool	Init(void);
	bool	Main_Menu(void);
	bool	Create_Game(Lib2D::Control*, void*);
	bool	Join_Game(Lib2D::Control*, void*);
	bool	Create_editor_menu_ctx(void);
public:
		Menu();
	bool	Create_Menu(void);
};

#endif
