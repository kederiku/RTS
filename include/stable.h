#ifndef __STABLE_H__
#define __STABLE_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class   Stable : public Building
{
	public:
		Stable(const char*);
	bool	Init_Interface(Player* player);
	bool	product(Lib2D::Control*, void* data);
};

#endif

