#ifndef __BARRACK_H__
#define __BARRACK_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class	Barrack : public Building
{
public:
	Barrack(const char* name, int id_player = -1);
	virtual ~Barrack(void);

	bool		Init_Interface(Player* player);
	bool		product(Player* player, int value, std::list<Unit*>* unit_in_construct);
};

#endif
