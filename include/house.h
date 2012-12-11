#ifndef __HOUSE_H__
#define __HOUSE_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class House : public Building
{
	public:
			House(const char*);
	bool	Init_Interface(Player* player);
	bool	product(Lib2D::Control*, void* data);
};

#endif
