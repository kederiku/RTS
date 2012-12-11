#include "connection.h"
#include "ui.hpp"
#include "my_popup.h"
#include "ressources.h"
#include "env.hpp"
#include "ns_var.h"
#include "ui.h"

Connection::Connection(void): __popup(NULL)
{
}

Connection::~Connection(void)
{
}

bool
Connection::Init(void)
{
	try
	{
		this->__context_create = new Lib2D::Context;
		this->__context_join = new Lib2D::Context;
	}
	catch(...)
	{
		return false;
	}
	return true;
}

bool
Connection::Add_child_to_context(Lib2D::Context* context)
{
	this->__background->resize(900, 800);
	this->__link_return->resize(230, 32);
	this->__button_label_send->resize(90, 40);
	this->__background->move(0, 0);
	this->__link_return->move(400, 750);
	this->__background->load_bmp(MENU);
	if (add_children(context, create_label("Adress", 200, 200, 25)) == false)
		return false;
	if (add_children(context, create_label("Port", 200, 260, 25)) == false)
		return false;
	this->__box_adress = create_txt_box<Lib2D::TextBox>(300, 32, 290, 200, -1);
	if (add_children(context, this->__box_adress) == false)
		return false;
	this->__box_port = create_txt_box<Lib2D::TextBox_num>(80, 32, 290, 260, 4);
	if (add_children(context, this->__box_port) == false)
		return false;
	if (this->__link_return->init("Return", FONT, 32, 0, 0XFFFFFFFF, false) == false)
	{
		delete this->__link_return;
	}
	if (this->__button_label_send->init_label("Send", FONT, 32, 0XFFFFFFFF) == false)
	{
		delete this->__button_label_send;
	}
		this->__button_label_send->signals.add(Lib2D::make_func(this, &Connection::Get_Value), 0, 0);
	this->__box_adress->set_value("twistedfate");
	if (add_children(context, this->__background, true) == false)
			return false;
	context->add_child(this->__button_label_send);
	context->add_child(this->__link_return);
	return true;
}

bool
Connection::Setting_Connection(bool create)
{
	try
	{
		this->__link_return = new Lib2D::Label_link;
		this->__button_label_send = new Lib2D::Button_label;
		this->__background = new Lib2D::Image;
	}
	catch(...)
	{
		return false;
	}
	if (create == true)
	{
		if (add_children(this->__context_create, create_label("Create game", 350, 20, 40)) == false)
			return false;
		this->__box_nb_player = create_txt_box<Lib2D::TextBox_num>(40, 32, 550, 260, 1);
		if (add_children(this->__context_create, this->__box_nb_player) == false)
			return false;
		if (add_children(this->__context_create, create_label("NB Player", 420, 260, 25)) == false)
			return false;
		this->__button_label_send->move(500, 305);
		this->Add_child_to_context(this->__context_create);
		if (this->__link_return->signals.add(Lib2D::make_func(this, &Connection::Delete_Child), 0, 0) == false)
			return false;
	}
	else
	{
		if (add_children(this->__context_join, create_label("Join game", 335, 20, 40)) == false)
			return false;
		this->__button_label_send->move(500, 305);
		this->Add_child_to_context(this->__context_join);
		if (this->__link_return->signals.add(Lib2D::make_func(this, &Connection::Delete_Child), 0, 0) == false)
			return false;
	}
	this->__create = create;
	return true;
}

Lib2D::Context*
Connection::Get_Context_Create()
{
	return this->__context_create;
}

Lib2D::Context*
Connection::Get_Context_Join()
{
	return this->__context_join;
}

void
Connection::Del_child_to_context(Lib2D::Context* context)
{
	unsigned	i(0);

	while (i < context->children())
	{
		context->del_child(i);
		++i;
	}
	this->__popup = NULL;
}

bool	Connection::create_server(void)
{
	const char*	port(this->__box_port->get_value());
	int		nb_player(ns_cmc::ns_var::f_atoi(this->__box_nb_player->get_value()));

	if (nb_player < 1 || nb_player > 8)
		return this->create_popup(this->__context_create, "erreur nb player");
	if (ns_cmc::ns_var::f_str_len(port) != 4)
		return this->create_popup(this->__context_create, "erreur port");
	if (this->__popup != NULL)
		return true;
	if (Env::get_instance()->server.init(port, 0, nb_player) == true)
	{
		if (Env::get_instance()->client.init(port, 0) == false)
		{
			Env::get_instance()->server.clear();
			return this->create_popup(this->__context_create, "imposible de joindre le serveur");
		}
		return this->create_popup(this->__context_create, "create server succes");
	}
	else
		return this->create_popup(this->__context_create, "create server fail");
	return true;
}

bool
Connection::Get_Value(Lib2D::Control*, void*)
{
	if (this->__create == true)
		return this->create_server();
	else
		return this->join_server();
	return true;
}

bool
Connection::Delete_Child(Lib2D::Control*, void*)
{
	if (this->__create == true)
		this->Del_child_to_context(this->__context_create);
	else
		this->Del_child_to_context(this->__context_join);
	return true;
}

bool	Connection::create_popup(Lib2D::Context* ctx, const char* title)
{
	this->__popup = new (std::nothrow) Lib2D::Popup_m;
	if (this->__popup == 0)
		return false;
	this->__popup->resize(250, 250);
	this->__popup->move(175, 175);
	if (this->__popup->init(title, FONT, false) == false || ctx->add_child(this->__popup) == false)
	{
		delete this->__popup;
		this->__popup = NULL;
		return false;
	}
	if (add_button_label(this->__popup, "Ok", 60, 70, &Connection::del_popup, this, ctx) == false)
		return false;
	return true;
}


bool	Connection::del_popup(Lib2D::Control*, void* data)
{
	Lib2D::Context*	ctx((Lib2D::Context*)data);
	Lib2D::Window*	window(Lib2D::Window::get_instance());

	ctx->del_child(this->__popup);
	this->__popup = NULL;
	if (Env::get_instance()->client.is_run() == true)
		window->context(3);
	return true;
}


bool	Connection::join_server(void)
{
	const char*	port(this->__box_port->get_value());
	const char*	address(this->__box_adress->get_value());

	if (this->__popup != NULL)
		return true;
	if (Env::get_instance()->client.init(port, address) == true)
		return this->create_popup(this->__context_join, "join server succes");
	else
		return this->create_popup(this->__context_join, "join server fail");
	return true;
}
