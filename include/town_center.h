#ifndef __TOWN_CENTER_H__
#define __TOWN_CENTER_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class Town_Center : public Building
{
public:
	Town_Center(const char* name, int id_player = -1);
	virtual ~Town_Center(void);

	bool		Init_Interface(Player* player);
	bool		product(Player* player, int value, std::list<Unit*>* unit_in_construct);
};

#endif
