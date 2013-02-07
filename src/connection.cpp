#include "connection.h"
#include "ui.hpp"
#include "my_popup.h"
#include "ressources.h"
#include "env.hpp"
#include "ns_var.h"
#include "ui.h"
#include "menugame.h"

Connection::Connection(void): __box_adress(0), __box_port(0), __box_nb_player(0),
			      __link_return(0), __button_label_send(0), __context_create(0),
			      __context_join(0), __popup(NULL), __context_popup(0)
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
	this->__link_return = new (std::nothrow)Lib2D::Label_link;

	if (add_children(context, this->__link_return) == false ||
	    this->__link_return->init("Return", FONT, 32, 0, 0XFFFFFFFF, false) == false ||
	    this->__link_return->signals.add(Lib2D::make_func(this, &Connection::Delete_Child), 0, 0) == false)
		return false;

	this->__link_return->resize(230, 32);
	this->__link_return->move(400, 750);
	this->__button_label_send = create_button_label("Send", 500, 305, &Connection::Get_Value, this, 0);

	if (add_children(context, this->__button_label_send) == false)
		return false;

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

	if (add_children(context, create_bg(MENU, 900, 800), true) == false)
			return false;
	this->__context_popup = context;
	return true;
}

bool
Connection::Setting_Connection(bool create)
{
	this->__create = create;
	if (this->__context_popup != 0 && this->__popup != 0)
	{
		this->__context_popup->del_child(this->__popup);
		this->__popup = NULL;
	}
	if (create == true)
	{
		if (this->__context_create->children() > 0)
			return true;
		if (add_children(this->__context_create, create_label("Create game", 350, 20, 40)) == false)
			return false;
		this->__box_nb_player = create_txt_box<Lib2D::TextBox_num>(40, 32, 550, 260, 1);
		if (add_children(this->__context_create, this->__box_nb_player) == false)
			return false;
		if (add_children(this->__context_create, create_label("NB Player", 420, 260, 25)) == false)
			return false;
		return this->Add_child_to_context(this->__context_create);
	}
	else
	{
		if (this->__context_join->children() > 0)
			return true;
		if (add_children(this->__context_join, create_label("Join game", 335, 20, 40)) == false)
			return false;
		return this->Add_child_to_context(this->__context_join);
	}
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
}

bool	Connection::create_server(void)
{
	const char*	port(this->__box_port->get_value());
	int		nb_player(ns_cmc::ns_var::f_atoi(this->__box_nb_player->get_value()));

	if (nb_player < 1 || nb_player > 8)
		return this->create_popup(this->__context_create, "erreur nb player");
	if (ns_cmc::ns_var::f_str_len(port) != 4)
		return this->create_popup(this->__context_create, "erreur port");
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
	if (this->__popup != NULL)
		return true;
	if (this->__create == true)
		return this->create_server();
	else
		return this->join_server();
	return true;
}

bool
Connection::Delete_Child(Lib2D::Control*, void*)
{
//	if (this->__create == true)
//		this->Del_child_to_context(this->__context_create);
//	else
//		this->Del_child_to_context(this->__context_join);
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

	if (Env::get_instance()->client.is_run() == true)
	{
		((Menugame*)window->get_real_context(3))->delete_popup();
		window->context(3);
	}
	else
	{
		ctx->del_child(this->__popup);
		this->__popup = NULL;
	}
	return true;
}


bool	Connection::join_server(void)
{
	const char*	port(this->__box_port->get_value());
	const char*	address(this->__box_adress->get_value());

	if (Env::get_instance()->client.init(port, address) == true)
		return this->create_popup(this->__context_join, "join server succes");
	else
		return this->create_popup(this->__context_join, "join server fail");
	return true;
}
