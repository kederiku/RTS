#ifndef __DRUIDE_H__
#define __DRUIDE_H__

#include "unit.h"

class	Druide : public Unit
{
	public:
		Druide(const char*);
	bool	action(void);
};

#endif
