#include "player.h"
#include "unit.h"
#include "nation.h"

Player::Player(Nation* nation)
{
	this->__nation = nation;
	this->__is_player = false;
	this->__unemployed = 10;
}

Player::~Player(void)
{
	delete this->__nation;
}

void
Player::set_player(void)
{
	this->__is_player = true;
}

bool
Player::get_player(void)
{
	return this->__is_player;
}

int
Player::get_unemployed(void)
{
	return this->__unemployed;
}

void
Player::set_unemployed(int add)
{
	this->__unemployed += add;
}
