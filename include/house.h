#ifndef __HOUSE_H__
#define __HOUSE_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class House : public Building
{
public:
	House(const char*, int id_player = -1);
	virtual ~House(void);

	bool		Init_Interface(Player* player);
	bool		product(Player* player, int value, std::list<Unit*>* unit_in_construct);
};

#endif
