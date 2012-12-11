#ifndef __WALL_H__
#define __WALL_H__

#include "building.h"

class Wall : public Building
{
	public:
		Wall(const char* name);
	bool	product(Lib2D::Control*, void* data);
};

#endif
