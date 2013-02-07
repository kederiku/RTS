#include "warrior.h"
#include "ressources.h"

Warrior::Warrior(const char* name, int id_player) : Unit(name, 250, 15, 3, 35, id_player)
{
	this->__costs.gold = 40;
	this->__costs.wood = 0;
	this->__costs.population = 1;
	this->__type = WARRIOR;
	this->__iconpoint.x = 425;
	this->__iconpoint.y = 150;
}

