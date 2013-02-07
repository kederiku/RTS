#ifndef __ARCHERY_RANGE_H__
#define __ARCHERY_RANGE_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class Archery_Range : public Building
{
public:
	Archery_Range(const char*, int id_player = -1);
	virtual ~Archery_Range(void);

	bool		Init_Interface(Player* player);
	bool		product(Player* player, int value, std::list<Unit*>* unit_in_construct);
};

#endif
