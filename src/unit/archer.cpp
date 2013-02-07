#include "archer.h"
#include "ressources.h"

Archer::Archer(const char* name, int id_player) : Unit(name, 175, 12, 18, 45, id_player)
{
	this->__costs.gold = 20;
	this->__costs.wood = 0;
	this->__costs.population = 1;
	this->__type = ARCHER;
	this->__iconpoint.x = 325;
	this->__iconpoint.y = 100;
}
