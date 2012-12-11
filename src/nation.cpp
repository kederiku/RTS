#include "nation.h"
#include "archer.h"
#include "druide.h"
#include "warrior.h"
#include "mage.h"
#include "knight.h"
#include "ressources.h"

Nation::Nation(void)
{
	this->__image = 0;
	this->is_select = false;
}

bool			Nation::init_nation(e_land land, t_pos pos)
{
	Lib2D::Image*	image(NULL);

	try
	{
		this->__image = new Lib2D::Container;
	}
	catch(...)
	{
		return false;
	}
	this->__land = land;
	this->__image->resize(200, 300);
	this->__image->move(pos.x, pos.y);
	this->__image->init();
	if (this->__land == ENGLAND)
		image = this->set_england();
	else if (this->__land == FRANCE)
		image = this->set_france();
	else if (this->__land == GERMANY)
		image = this->set_germany();
	else if (this->__land == JAPAN)
		image = this->set_japan();
	else if (this->__land == USA)
		image = this->set_usa();
	if (image == NULL)
		return false;
	this->__image->add_child(image);
	return true;
}

Lib2D::Image*			Nation::del_unit(Lib2D::Image* image, Unit* unit1, Unit* unit2, Unit* unit3)
{
	delete image;
	delete unit1;
	delete unit2;
	delete unit3;
	return 0;
}

Lib2D::Image*			Nation::set_england(void)
{
	Lib2D::Image*	image = 0;
	Druide*		druide = 0;
	Archer*		archer = 0;
	Warrior*	warrior = 0;

	try
	{
		image = new Lib2D::Image;
		druide = new Druide("druide");
		archer = new Archer("robin");
		warrior = new Warrior("richard the lionheart");
	}
	catch(...)
	{
		return this->del_unit(image, druide, archer, warrior);
	}
	image->load_bmp(ENG);
	if (image == 0)
		return this->del_unit(image, druide, archer, warrior);
	this->__units.push_back(druide);
	this->__units.push_back(archer);
	this->__units.push_back(warrior);
	return image;
}

Lib2D::Image*			Nation::set_france(void)
{
	Lib2D::Image*	image = 0;
	Mage*		mage = 0;
	Knight*		knight = 0;
	Warrior*	warrior = 0;

	try
	{
		image = new Lib2D::Image;
		mage = new Mage("merlin");
		knight = new Knight("les chevaliers de la table ronde");
		warrior = new Warrior("templiers");
	}
	catch(...)
	{
		return this->del_unit(image, mage, knight, warrior);
	}
	image->load_bmp(FRA);
	if (image == 0)
		return this->del_unit(image, mage, knight, warrior);
	this->__units.push_back(mage);
	this->__units.push_back(knight);
	this->__units.push_back(warrior);
	return image;
}

Lib2D::Image*			Nation::set_germany(void)
{
	Lib2D::Image*	image = 0;
	Archer*		archer = 0;
	Knight*		knight = 0;
	Warrior*	warrior = 0;

	try
	{
		image = new Lib2D::Image;
		archer = new Archer("guilaume tell");
		knight = new Knight("were wolf");
		warrior = new Warrior("Vampyr");
	}
	catch(...)
	{
		return this->del_unit(image, archer, knight, warrior);
	}
	image->load_bmp(GER);
	if (image == 0)
		return this->del_unit(image, archer, knight, warrior);
	this->__units.push_back(archer);
	this->__units.push_back(knight);
	this->__units.push_back(warrior);
	return image;
}

Lib2D::Image*			Nation::set_japan(void)
{
	Lib2D::Image*	image = 0;
	Druide*		druide = 0;
	Archer*		archer = 0;
	Warrior*	warrior = 0;

	try
	{
		image = new Lib2D::Image;
		druide = new Druide("mog");
		archer = new Archer("mecha");
		warrior = new Warrior("samurai");
	}
	catch(...)
	{
		return this->del_unit(image, archer, druide, warrior);
	}
	image->load_bmp(JAP);
	if (image == 0)
		return this->del_unit(image, archer, druide, warrior);
	this->__units.push_back(druide);
	this->__units.push_back(archer);
	this->__units.push_back(warrior);
	return image;
}

Lib2D::Image*			Nation::set_usa(void)
{
	Lib2D::Image*	image = 0;
	Archer*		archer = 0;
	Knight*		knight = 0;
	Warrior*	warrior = 0;

	try
	{
		image = new Lib2D::Image;
		archer = new Archer("bomb");
		knight = new Knight("cow boy");
		warrior = new Warrior("indian");
	}
	catch(...)
	{
		return this->del_unit(image, archer, knight, warrior);
	}
	image->load_bmp(US);
	if (image == 0)
		return this->del_unit(image, archer, knight, warrior);
	this->__units.push_back(archer);
	this->__units.push_back(knight);
	this->__units.push_back(warrior);
	return image;
}

Lib2D::Container*	Nation::get_container(void)
{
	return this->__image;
}

e_land			Nation::get_land(void)
{
	return this->__land;
}
