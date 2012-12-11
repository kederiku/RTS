#ifndef __BARRACK_H__
#define __BARRACK_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class	Barrack : public Building
{
public:
		Barrack(const char* name);
	bool	Init_Interface(Player* player);
	bool	product(Lib2D::Control*, void* data);
};

#endif
