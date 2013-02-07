#ifndef __TOWER_H__
#define __TOWER_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class	Tower : public Building
{
public:
	Tower(const char*, int id_player = -1);
	~Tower(void);

	bool		Init_Interface(Player* player);
	bool		product(Player* player, int value, std::list<Unit*>*);
};

#endif
