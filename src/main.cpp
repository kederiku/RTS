#include <iostream>
#include <SDL/SDL.h>
#include <Lib2D.h>
#include "env.hpp"
#include "menu.h"

Env*		Env::__instance = 0;
pthread_mutex_t	Env::__mutex;
int
error(const char* err, Lib2D::Engine& engine)
{
	(void)err;
	engine.cleaner();
	Env::kill();
	return -1;
}

int
main(void)
{
	Lib2D::Engine		engine;
	Menu			menu;
	Env*			env;

	try
	{
		if (engine.init() == false)
			return error("could not init Lib2D", engine);
		if (engine.init_main_window(900, 800, 32, Lib2D::E_HARDWARE) == false)
			return error("could not init main window", engine);
		env = Env::get_instance();
		if (env == 0)
			return error("could not env", engine);
		if(menu.Create_Menu() == false)
			return -1;
		if (engine.run() == false)
			return error("program terminated unexpectedly", engine);
		engine.cleaner();
		Env::kill();
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}
