#ifndef __ARCHER_H__
#define __ARCHER_H__

#include "unit.h"

class	Archer : public Unit
{
	public:
		Archer(const char* name, int id_player = -1);
};

#endif
