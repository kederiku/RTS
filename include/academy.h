#ifndef __ACADEMY_H__
#define __ACADEMY_H__

#include <Lib2D.h>
#include "building.h"
#include "inter.h"

class	Academy : public Building
{
public:
		Academy(const char*, int id_player = -1);
	virtual	~Academy(void);

	bool	Init_Interface(Player* player);
	bool	product(Player* player, int value, std::list<Unit*>* unit_in_construct);
};

#endif

