#include "druide.h"
#include "ressources.h"

Druide::Druide(const char* name, int id_player) : Unit(name, 100, 15, 20, 45, id_player)
{
	this->__costs.gold = 40;
	this->__costs.wood = 0;
	this->__costs.population = 2;
	this->__type = DRUIDE;
	this->__iconpoint.x = 325;
	this->__iconpoint.y = 650;
}
