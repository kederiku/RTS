#include "knight.h"
#include "ressources.h"

Knight::Knight(const char* name, int id_player) : Unit(name, 200, 15, 6, 60, id_player)
{
	this->__costs.gold = 40;
	this->__costs.wood = 0;
	this->__costs.population = 2;
	this->__type = KNIGHT;
	this->__iconpoint.x = 325;
	this->__iconpoint.y = 200;
}

