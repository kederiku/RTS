#ifndef __TOWER_H__
#define __TOWER_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class	Tower : public Building
{
	public:
		Tower(const char*);
	bool	Init_Interface(Player* player);
	bool	product(Lib2D::Control*, void* data);
};

#endif
