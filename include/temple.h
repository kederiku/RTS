#ifndef __TEMPLE_H__
#define __TEMPLE_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class	Temple : public Building
{
public:
		Temple(const char*, int id_player = -1);
	virtual	~Temple(void);

	bool	Init_Interface(Player* player);
	bool	product(Player* player, int value, std::list<Unit*>* unit_in_construct);
};

#endif

