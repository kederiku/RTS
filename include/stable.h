#ifndef __STABLE_H__
#define __STABLE_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class	Stable : public Building
{
public:
		Stable(const char*, int id_player = -1);
	virtual	~Stable(void);

	bool	Init_Interface(Player* player);
	bool	product(Player* player, int value, std::list<Unit*>* unit_in_construct);
};

#endif

