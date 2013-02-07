#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "unit.h"

class	Warrior : public Unit
{
	public:
		Warrior(const char* name, int id_player = -1);
};

#endif
