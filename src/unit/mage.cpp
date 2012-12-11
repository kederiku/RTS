#include "mage.h"

Mage::Mage(const char* name) : Unit(name, 150, 17, 17, 20)
{
}

bool	Mage::action(void)
{
	//-40pv aux ennemis
	return true;
}
