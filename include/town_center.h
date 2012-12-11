#ifndef __TOWN_CENTER_H__
#define __TOWN_CENTER_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class Town_Center : public Building
{
	public:
		Town_Center(const char* name);
	bool	Init_Interface(Player* player);
	bool	product(Lib2D::Control*, void* data);
};

#endif
