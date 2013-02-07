#include "mage.h"
#include "ressources.h"

Mage::Mage(const char* name, int id_player) : Unit(name, 150, 17, 17, 303030, id_player)
{
	this->__costs.gold = 40;
	this->__costs.wood = 0;
	this->__costs.population = 2;
	this->__type = MAGE;
	this->__iconpoint.x = 325;
	this->__iconpoint.y = 50;
}
