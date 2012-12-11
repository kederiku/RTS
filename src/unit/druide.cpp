#include "druide.h"

Druide::Druide(const char* name) : Unit(name, 100, 15, 20, 20)
{
}

bool	Druide::action(void)
{
	//+35 pv a tous les allies aux alentours de 15m
	return true;
}
