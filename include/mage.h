#ifndef __MAGE_H__
#define __MAGE_H__

#include "unit.h"

class	Mage : public Unit
{
	public:
		Mage(const char*);
	bool	action(void);
};

#endif
