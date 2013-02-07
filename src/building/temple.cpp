#include "temple.h"
#include "ressources.h"
#include "druide.h"
#include "player.h"
#include "env.hpp"

Temple::Temple(const char* name, int id_player) : Building(name, 2250, 20, 18, 60, id_player)
{
	this->__type = TEMPLE;
	this->__finish_pos.x = 96;
	this->__finish_pos.y = 657;
	this->__finish_pos.w = 95;
	this->__finish_pos.h = 85;
	this->__product = DRUIDE;
	this->__costs.wood = 250;
	this->__costs.gold = 150;
}

Temple::~Temple(void)
{
}

bool
Temple::Init_Interface(Player* player)
{
	Lib2D::Image	img_source;
	Lib2D::Image*	image[2];
	Druide*		druide = new Druide("Druide");

	if ((this->__inter = new (std::nothrow)Inter) == 0)
	{
		delete this->__inter;
		return false;
	}
	img_source.load_bmp(ICON);
	image[0] = img_source.get_image_part(275, 650, 50, 50);
	image[1] = img_source.get_image_part(325, 650, 50, 50);
	if (image[0] == 0 || image[1] == 0)
		return false;
	return this->__inter->Init_Interface(image, this->__name, player, this, druide);
}

bool	Temple::product(Player* player, int value, std::list<Unit*>* unit_in_construct)
{
	Druide*		druides;
	int		i(0);

	this->__state = BACTION;
	while (i < value)
	{
		druides = new (std::nothrow)Druide("Druide", player->get_id_player());
		if (druides == 0)
			return false;
		if (druides->get_costs().wood > player->get_wood() || druides->get_costs().gold > player->get_gold())
		{
			delete druides;
			return true;
		}
		if (druides->init() == false)
		{
			delete druides;
			return false;
		}
		player->set_wood(-druides->get_costs().wood);
		player->set_gold(-druides->get_costs().gold);
		druides->set_producer(this);
		unit_in_construct->push_back(druides);
		if (i == 0)
			druides->begin_product();
		i++;
	}
	return true;
}
