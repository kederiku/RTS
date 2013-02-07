#include "unit.h"
#include "inter.h"
#include "building.h"
#include "ressources.h"
#include "s_ressources.h"
#include "player.h"
#include "ns_var.h"
#include "env.hpp"
#include "tools.h"
#include "ui.hpp"
#include "ui.h"

Inter::Inter(): Container(), __id_building(0)
{
	this->move(750, 0);
	this->resize(150, 800);
}

Inter::~Inter()
{
}

bool
Inter::Init_Interface(Lib2D::Image** img, const char* name, Player* player, Building* building, Unit* unit)
{
	Lib2D::Image	img_src;

	img_src.load_bmp(ICON);
	if (Head_Inter_Building(img[0], name, building) == false)
		return false;
	if (building->get_type() != HOUSE && building->get_type() != TOWER &&
	    building->get_state() != BACTION && building->get_state() != BNONE &&
	    this->Init_Production(player) == false)
		return false;
	this->__id_building = building;
	if (img[1] == NULL)
		return true;
	img[1]->move(10, 150);
	img[1]->resize(50, 50);
	if (this->Add_Icon(GOLD, 150) == false || this->Add_Icon(POPU, 170) == false)
		return false;
	if (unit == 0)
		return true;
	Add_Label(unit);
	delete unit;
	this->add_child(img[1]);
	return true;
}

bool
Inter::Head_Inter_Unit(Lib2D::Image* img, const char* name, Unit* unit)
{
	char		hp[22];
	unsigned	str_len;

	id::itoa(unit->get_hp(), hp);
	str_len = ns_cmc::ns_var::f_str_len(hp);
	hp[str_len] = '/';
	id::itoa(unit->get_hp_max(), hp + str_len + 1);
	return this->Head_Inter(img, hp, name);
}

bool
Inter::Head_Inter_Ressource(Lib2D::Image* img, const char* name, Ressources* ressource)
{
	char		hp[22];
	unsigned	str_len;

	id::itoa(ressource->get_capacity(), hp);
	str_len = ns_cmc::ns_var::f_str_len(hp);
	hp[str_len] = '/';
	id::itoa(ressource->get_capacity_max(), hp + str_len + 1);
	return this->Head_Inter(img, hp, name);
}

bool
Inter::Head_Inter_Building(Lib2D::Image* img, const char* name, Building* building)
{
	char		hp[22];
	unsigned	str_len;

	id::itoa(building->get_hp(), hp);
	str_len = ns_cmc::ns_var::f_str_len(hp);
	hp[str_len] = '/';
	id::itoa(building->get_hp_max(), hp + str_len + 1);
	return this->Head_Inter(img, hp, name);
}

bool
Inter::Head_Inter(Lib2D::Image* img, char* hp, const char* name)
{
	if (add_children(this, create_label(hp, 65, 50, 14, 0XCECECEFF)) == false)
		return false;
	if (add_children(this, create_label(name, 10, 110, 22, 0XCECECEFF)) == false)
		return false;
	img->move(10, 50);
	img->resize(50,50);
	this->add_child(img);
	return true;
}

void
Inter::Delete_Interface()
{
	for (int a = this->children() -1; a > -1; a--)
		this->del_child(a);
	this->clean();
}

bool
Inter::Init_Production(Player* player)
{
	Lib2D::TextBox_num*	txtbox = 0;
	Lib2D::Button_label*	blabel = 0;
	Lib2D::Button_label*	plus = 0;
	Lib2D::Button_label*	minus = 0;

	txtbox = new (std::nothrow) Lib2D::TextBox_num;
	blabel = new (std::nothrow) Lib2D::Button_label;
	plus = new (std::nothrow) Lib2D::Button_label;
	minus = new (std::nothrow) Lib2D::Button_label;
	if (txtbox == 0 || blabel == 0 || plus == 0 || minus == 0)
	{
		delete txtbox;
		delete blabel;
		delete plus;
		delete minus;
		return false;
	}
	txtbox->move(50, 550);
	txtbox->resize(50, 25);
	blabel->move(50, 580);
	blabel->resize(50, 25);
	plus->move(105, 550);
	plus->resize(15, 12);
	minus->move(105, 563);
	minus->resize(15, 12);
	if (txtbox->init(FONT, 20, 3) == false || blabel->init_label("OK", FONT, 16) == false ||
	    plus->init_label("+", FONT, 16) == false || minus->init_label("-", FONT, 16) == false ||
	    this->add_child(txtbox) == false || this->add_child(blabel) == false ||
	    this->add_child(plus) == false || this->add_child(minus) == false)
	{
		delete txtbox;
		delete blabel;
		delete plus;
		delete minus;
		return false;
	}
	txtbox->set_value("1");
	plus->signals.add(Lib2D::make_func(this, &Inter::Plus), txtbox, player);
	minus->signals.add(Lib2D::make_func(this, &Inter::Minus), txtbox, 0);
	blabel->signals.add(Lib2D::make_func(this, &Inter::Launch_product), txtbox, player);
	return true;
}

bool
Inter::Plus(Lib2D::Control* control, void* data)
{
	Lib2D::TextBox_num*	txtbox = (Lib2D::TextBox_num*)control;
	Player*			player = (Player*)data;
	int			value = ns_cmc::ns_var::f_atoi(txtbox->get_value());
	char			buffer[11];

	if (value >= player->get_employed_max() - player->get_unemployed())
		return false;
	++value;
	id::itoa(value, buffer);
	txtbox->set_value(buffer);
	return true;
}

bool
Inter::Minus(Lib2D::Control* control, void*)
{
	Lib2D::TextBox_num*	txtbox = (Lib2D::TextBox_num*)control;
	int			value = ns_cmc::ns_var::f_atoi(txtbox->get_value());
	char			buffer[11];

	if (value < 2)
		return false;
	--value;
	id::itoa(value, buffer);
	txtbox->set_value(buffer);
	return true;
}


bool
Inter::Launch_product(Lib2D::Control* control, void* data)
{
	Lib2D::TextBox_num*	txtbox = (Lib2D::TextBox_num*)control;
	Player*			player = (Player*)data;
	int			value = ns_cmc::ns_var::f_atoi(txtbox->get_value());
	int			gold = 40;

	if (value > (player->get_employed_max() - player->get_unemployed() + player->get_in_product()) || value < 1)
		return false;
	if (this->__id_building->get_product() == PEON)
		gold = 0;
	else if (this->__id_building->get_product() == ARCHER)
		gold = 20;
	if (gold * value > player->get_gold())
		return false;
	Env::get_instance()->client.send_unit(this->__id_building->get_id(), player->get_id_player(), value);
	return true;
}

bool
Inter::Add_Icon(e_ressource type, int y)
{
	Lib2D::Subimage*	image;

	image = new (std::nothrow) Lib2D::Subimage;
	if (image == 0 ||
	    Env::get_instance()->ressource.init_subimage_icon_ressource(image, type) == false ||
	    this->add_child(image) == false)
	{
		delete image;
		return false;
	}
	image->move(65, y);
	return true;
}

bool
Inter::Add_Label(Unit* unit)
{
	if (add_children(this, create_label(unit->get_costs().gold, 90, 150, 20, 0XCECECEFF)) == false)
		return false;
	if (add_children(this, create_label(unit->get_costs().population, 90, 170, 20, 0XCECECEFF)) == false)
		return false;
	return true;
}

