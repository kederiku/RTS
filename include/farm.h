#ifndef __FARM_H__
#define __FARM_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class	Farm : public Building
{
	public:
		Farm(const char* name);
	bool	Init_Interface(Player* player);
	bool	product(Lib2D::Control*, void* data);
};

#endif
