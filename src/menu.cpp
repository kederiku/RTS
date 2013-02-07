#include "menu.h"
#include "menugame.h"
#include "ressources.h"
#include "game.h"
#include "map_editor.h"
#include "ui.hpp"
#include "connection.h"


Menu::Menu(): __connection(NULL), __background(NULL), __context(NULL), __title(NULL), __create(NULL), __join(NULL)
{
}

bool
Menu::Init()
{
	try
	{
		this->__connection = new Connection;
		this->__background = new Lib2D::Image;
		this->__context = new Lib2D::Context;
		this->__title = new Lib2D::Label;
		this->__create = new Lib2D::Label_link;
		this->__join = new Lib2D::Label_link;
	}
	catch(...)
	{
		delete this->__connection;
		delete this->__background;
		delete this->__context;
		delete this->__title;
		delete this->__create;
		delete this->__join;
		return false;
	}
	return true;
}
bool
Menu::Create_Menu(void)
{
	Lib2D::Window*		window;
	Menugame*		menugame = new (std::nothrow) Menugame;

	if (menugame == 0)
		return false;

	window = Lib2D::Window::get_instance();
	if (Init() == false)
		return false;
	if (Main_Menu() == false)
		return false;
	if (this->__connection->Init() == false)
		return false;
	if (menugame->init_menugame() == false)
		return false;
	window->add_context(this->__context);
	window->add_context(this->__connection->Get_Context_Create());
	window->add_context(this->__connection->Get_Context_Join());
	window->add_context(menugame);
	if (this->Create_editor_menu_ctx() == false)
		return false;
	return true;
}

bool
Menu::Main_Menu(void)
{
	this->__background->move(0, 0);
	this->__background->resize(900, 800);
	this->__background->load_bmp(MENU);
	if (this->__background == NULL)
		return false;
	this->__title->move(20, 30);
	if (this->__title->init("DAWN OF TOTAL CONQUER", FONT, 70, 0XCECECEFF, false) == false)
		return false;
	this->__create->resize(230, 32);
	this->__create->move(340, 350);
	this->__create->init("Create Game", FONT, 45, 1, 0XCECECEFF, false);
	if (this->__create->signals.add(Lib2D::make_func(this, &Menu::Create_Game), 0, 0) == false)
		return false;
	this->__join->resize(230, 32);
	this->__join->move(365, 400);
	this->__join->init("Join Game", FONT, 45, 2, 0XCECECEFF, false);
	if (this->__join->signals.add(Lib2D::make_func(this, &Menu::Join_Game), 0, 0) == false)
		return false;
	this->__context->add_child(this->__background);
	this->__context->add_child(this->__title);
	this->__context->add_child(this->__create);
	this->__context->add_child(this->__join);
	return true;
}

bool
Menu::Create_Game(Lib2D::Control* control, void* data)
{
	(void)data;
	(void)control;
	if(this->__connection->Setting_Connection(true) == false)
		return false;
	return true;
}

bool
Menu::Join_Game(Lib2D::Control* control, void* data)
{
	(void)data;
	(void)control;
	if(this->__connection->Setting_Connection(false) == false)
		return false;
	return true;
}

bool	Menu::Create_editor_menu_ctx(void)
{
	Lib2D::Window*		window(Lib2D::Window::get_instance());
	Lib2D::Context*		context(0);
	Map_editor*		map_editor;
	Lib2D::Label_link*	link;

	context = new (std::nothrow)Lib2D::Context;
	if (context == 0 || window->add_context(context) == false)
	{
		delete context;
		return false;
	}
	map_editor = new (std::nothrow) Map_editor;
	if (map_editor == 0)
		return false;
	map_editor->resize(900, 800);
	map_editor->move(0, 0);
	if (map_editor->init() == false || context->add_child(map_editor) == false)
	{
		delete map_editor;
		return false;
	}
	link = new (std::nothrow) Lib2D::Label_link;
	if (link == 0)
		return false;
	link->resize(50, 50);
	link->move(350, 450);
	if (link->init("Map editor", FONT, 45, 4, 0XCECECEFF, false) == false ||
	    this->__context->add_child(link) == false)
		return false;
	return true;
}

