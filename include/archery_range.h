#ifndef __ARCHERY_RANGE_H__
#define __ARCHERY_RANGE_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class Archery_Range : public Building
{
	public:
		Archery_Range(const char*);
	bool	Init_Interface(Player* player);
	bool	product(Lib2D::Control*, void* data);
};

#endif
