#include "inter.h"
#include "building.h"
#include "ressources.h"
#include "player.h"
#include "ns_var.h"

Inter::Inter(): Container(), value(-1), launch_product(false)
{
}

Inter::~Inter()
{
}

bool
Inter::Init_Interface(Lib2D::Image** img, const char* name, Player* player, Building* building)
{
	this->move(750, 0);
	this->resize(150, 800);
	if (Head_Inter(img[0], name, building) == false)
		return false;
	if (this->Init_Production(player) == false)
		return false;
	if (img[1] == NULL)
		return true;
	img[1]->move(10, 150);
	img[1]->resize(50, 50);
	this->add_child(img[1]);
	return true;
}

void
Inter::Delete_Interface()
{
	std::cout << "children: " << this->children() << std::endl;
	for (int a = this->children() -1; a > -1; a--)
		this->del_child(a);
	this->clean();
	std::cout << "children: " << this->children() << std::endl;
}

bool
Inter::Head_Inter(Lib2D::Image* img, const char* name, Building* building)
{
	std::cout << "pass"<< std::endl;
	char* hp = ns_cmc::ns_var::f_itoa(building->get_hp());
	char* hp_max = ns_cmc::ns_var::f_itoa(building->get_hp_max());

	try
	{
		this->__name = new Lib2D::Label;
		this->__life[0] = new Lib2D::Label;
		this->__life[1] = new Lib2D::Label;
		this->__life[2] = new Lib2D::Label;
	}
	catch(...)
	{
		return false;
	}
	img->move(10, 50);
	img->resize(50,50);
	this->add_child(img);
	this->__name->move(10, 110);
	if (this->__name->init(name, FONT, 22, 0XCECECEFF, false) == false)
		return false;
	this->__life[0]->move(65, 50);
	if (this->__life[0]->init(hp, FONT, 14, 0XCECECEFF, false) == false)
		return false;
	this->__life[1]->move(65 + this->__life[0]->pos().w, 50);
	if (this->__life[1]->init("/", FONT, 14, 0XCECECEFF, false) == false)
		return false;
	this->__life[2]->move(65 + this->__life[0]->pos().w + this->__life[1]->pos().w, 50);
	if (this->__life[2]->init(hp_max, FONT, 14, 0XCECECEFF, false) == false)
		return false;
	this->add_child(this->__life[0]);
	this->add_child(this->__life[1]);
	this->add_child(this->__life[2]);
	this->add_child(this->__name);
	return true;
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

	if (value >= player->get_unemployed())
		return false;
	value++;
	txtbox->set_value(ns_cmc::ns_var::f_itoa(value));
	return true;
}

bool
Inter::Minus(Lib2D::Control* control, void* data)
{
	Lib2D::TextBox_num*	txtbox = (Lib2D::TextBox_num*)control;
	int			value = ns_cmc::ns_var::f_atoi(txtbox->get_value());
	(void)data;

	if (value <= 1)
		return false;
	value--;
	txtbox->set_value(ns_cmc::ns_var::f_itoa(value));
	return true;
}

bool
Inter::Launch_product(Lib2D::Control* control, void* data)
{
	Lib2D::TextBox_num*	txtbox = (Lib2D::TextBox_num*)control;
	Player*			player = (Player*)data;
	int			value = ns_cmc::ns_var::f_atoi(txtbox->get_value());

	if (value > player->get_unemployed() || value < 1)
		return false;
	player->set_unemployed(-value);
	std::cout << "Value: " << value << std::endl;
	this->launch_product = true;
	this->value = value;
	//appeler product?
	return true;
}
