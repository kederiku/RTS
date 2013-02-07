#include "map_editor.h"
#include "ressources.h"
#include "point.h"
#include "ui.hpp"
#include "ns_var.h"
#include "container_game.h"
#include "env.hpp"

Map_editor::Map_editor(void):
	__container_map(0),
	__init(false),
	__popup(0),
	__sprite_img(0),
	__info(0),
	__sprite_list_info(0)
{
}

Map_editor::~Map_editor(void)
{
	delete [] this->__sprite_list_info;
	this->__sprite_list_info = 0;
}

bool	Map_editor::init_buttons(void)
{
	int	y(750);

	if (this->__init == true)
		return true;
	if (add_button_label(this, "New Map", 0, y, &Map_editor::create_popup_new_map, this, 0) == false)
		return false;
	if (add_button_label(this, "Add Field", 150, y, &Map_editor::create_popup_field, this, 0) == false)
		return false;
	if (add_button_label(this, "Add Ressource", 300, y, &Map_editor::create_popup_ressource, this, 0) == false)
		return false;
	if (add_button_label(this, "Save", 600, y, &Map_editor::save_map, this, 0) == false)
		return false;
	if (add_button_label(this, "Load", 750, y, &Map_editor::load_map, this, 0) == false)
		return false;
	this->__init = true;
	return true;
}

bool	Map_editor::create_popup_field(Lib2D::Control* , void*)
{
	if (this->is_popup_open() == true)
		return true;
	delete [] this->__sprite_list_info;
	this->__sprite_list_info = new (std::nothrow) info_sprite[19 * 20];
	if (this->__sprite_list_info == 0)
		return false;
	this->__popup = new (std::nothrow) My_popup;
	if (this->__popup == 0)
		return false;
	this->__popup->resize(19 * 32, 20 * 32);
	this->__popup->move(175, 75);
	if (add_children(this, this->__popup) == false || this->__popup->field(this, this->__sprite_list_info) == false)
		return false;
	return true;
}


bool	Map_editor::create_popup_ressource(Lib2D::Control* , void*)
{
	if (this->is_popup_open() == true)
		return true;
	delete [] this->__sprite_list_info;
	this->__sprite_list_info = new (std::nothrow) info_sprite[3];
	if (this->__sprite_list_info == 0)
		return false;
	this->__popup = new (std::nothrow) My_popup;
	if (this->__popup == 0)
		return false;
	this->__popup->resize(192, 128);
	this->__popup->move(175, 75);
	if (add_children(this, this->__popup) == false || this->__popup->ressource(this, this->__sprite_list_info) == false)
		return false;
	return true;
}

bool	Map_editor::create_popup_new_map(Lib2D::Control*, void*)
{
	if (this->is_popup_open() == true)
		return true;
	this->__popup = new (std::nothrow) My_popup;
	if (this->__popup == 0)
		return false;
	this->__popup->resize(325, 200);
	this->__popup->move(175, 75);
	if (add_children(this, this->__popup) == false || this->__popup->init_popupbox(this) == false)
		return false;
	return true;
}

bool	Map_editor::save_map(Lib2D::Control*, void*)
{
	if (this->is_popup_open() == true)
		return true;
	this->__popup = new (std::nothrow) My_popup;
	if (this->__popup == 0)
		return false;
	this->__popup->resize(325, 200);
	this->__popup->move(175, 75);
	if (this->__popup->init_save_and_load_popupbox(this, "Save file", &Map_editor::save_file) == false ||
	    this->add_child(this->__popup) == false)
	{
		delete this->__popup;
		this->__popup = 0;
		return false;
	}
	return true;
}

bool	Map_editor::save_file(Lib2D::Control*, void* data)
{
	Lib2D::TextBox**	txt((Lib2D::TextBox**)data);
	const char*		path = txt[0]->get_value();

	if (this->__container_map->save(path) == false)
		return false;
	return this->cancel(0, 0);
}

bool	Map_editor::load_map(Lib2D::Control*, void*)
{
	if (this->is_popup_open() == true)
		return true;
	if (this->__container_map == 0)
		return true;
	this->__popup = new (std::nothrow) My_popup;
	if (this->__popup == 0)
		return false;
	this->__popup->resize(325, 200);
	this->__popup->move(175, 75);
	if (this->__popup->init_save_and_load_popupbox(this, "Load file", &Map_editor::load_file) == false ||
	    this->add_child(this->__popup) == false)
	{
		delete this->__popup;
		this->__popup = 0;
		return false;
	}
	return true;
}

bool	Map_editor::load_file(Lib2D::Control*, void* data)
{
	Lib2D::TextBox**	txt((Lib2D::TextBox**)data);
	const char*		path = txt[0]->get_value();
	Container_game*		tmp;

	this->del_child(this->__container_map);
	this->__container_map = 0;
	tmp = new (std::nothrow) Container_game;
	if (add_children(this, tmp, true) == false || tmp->init(path, 700, 700) == false)
		return false;
	this->__container_map = tmp;
	return this->cancel(0, 0);
}

bool	Map_editor::cancel(Lib2D::Control*, void*)
{
	Multi::del_child(this->__popup);
	this->__popup = 0;
	return true;
}


bool	Map_editor::is_popup_open(void)
{
	if (this->__popup != 0)
		return true;
	return false;
}

bool	Map_editor::is_in_container_map(const Lib2D::s_mouse_event* mouse_event) const
{
	return (mouse_event->x < (int)this->__container_map->pos().w &&
		mouse_event->y < (int)this->__container_map->pos().h &&
		mouse_event->x > 0 &&
		mouse_event->y > 0);
}

bool	Map_editor::move_sprite(const Lib2D::s_mouse_event* mouse_event)
{
	if (this->__sprite_img == 0 || this->__container_map == 0)
		return true;
	if (this->is_in_container_map(mouse_event) == true)
	{
		this->__sprite_img->move(mouse_event->x, mouse_event->y);
		this->__sprite_img->visible(true);
	}
	else
		this->__sprite_img->visible(false);
	return true;
}

bool	Map_editor::add_sprite(const Lib2D::s_mouse_event* mouse_event)
{
	Point	pos(mouse_event->x, mouse_event->y);

	if (this->__sprite_img == 0 || this->__container_map == 0)
		return true;
	if (this->is_in_container_map(mouse_event) == false)
		return true;
	if (this->__info == 0)
		return true;
	if (this->__info->type == FIELD)
		return  this->__container_map->add_field(this->__info->pos, pos);
	else if (this->__info->type == RESSOURCE)
		return  this->__container_map->add_ressource(this->__info->ressource, pos);
	else
		return false;
	return true;
}

bool	Map_editor::derived_treat_event(Lib2D::Event* event)
{
	if (this->is_popup_open() == true)
		return true;
	switch (event->get_type())
	{
		case Lib2D::E_MOUSEMOTION_EVENT:
			return this->move_sprite(((Lib2D::Mouse_event*)event)->get_mouse_event());
		case Lib2D::E_MOUSEDOWN_EVENT:
			return this->add_sprite(((Lib2D::Mouse_event*)event)->get_mouse_event());
		default:
		       break;
	}
	return true;
}

bool	Map_editor::init(void)
{
	Container_game*		tmp;

	if (this->__init == true)
		return true;
	if (Container::init() == false)
		return false;
	tmp = new (std::nothrow) Container_game;
	if (add_children(this, tmp, true) == false || tmp->init(25, 25, 700, 700) == false)
		return false;
	if (this->__sprite_field.load_bmp(MAP) == false)
		return false;
	if (this->__sprite_ressource.load_bmp(RES) == false)
		return false;
	if (this->init_buttons() == false)
		return false;
	this->__init = true;
	this->__container_map = tmp;
	return true;
}

bool	Map_editor::new_size(Lib2D::Control*, void* data)
{
	Lib2D::TextBox_num**	txt((Lib2D::TextBox_num**)data);
	int			width(ns_cmc::ns_var::f_atoi(txt[0]->get_value()));
	int			height(ns_cmc::ns_var::f_atoi(txt[1]->get_value()));
	Container_game*		tmp;

	if (this->__container_map == 0)
		return false;
	if (width != 0 && height != 0)
	{
		this->del_child(this->__container_map);
		this->__container_map = 0;
		tmp = new (std::nothrow) Container_game;
		if (add_children(this, tmp, true) == false || tmp->init(width, height, 700, 700) == false)
			return false;
		this->__container_map = tmp;
	}
	cancel(0, 0);
	return true;
}

bool	Map_editor::set_sprite(Lib2D::Control*, void* data)
{
	Lib2D::Subimage*	tmp;
	bool			ret(false);

	this->__info = (info_sprite*)data;
	if (this->__sprite_img != 0)
		this->del_child(this->__sprite_img);
	this->__sprite_img = 0;
	if (this->__container_map == 0)
		return true;
	tmp = new (std::nothrow) Lib2D::Subimage;
	if (tmp == 0)
		return false;
	if (this->__info->type == FIELD)
		ret = Env::get_instance()->ressource.init_subimage_sprite_field(tmp, this->__info->pos, 32);
	else if (this->__info->type == RESSOURCE)
		ret = Env::get_instance()->ressource.init_subimage_ressource(tmp, this->__info->ressource);
	if (ret == false)
	{
		delete tmp;
		return false;
	}
	if (add_children(this, tmp) == false)
		return false;
	tmp->visible(false);
	this->__sprite_img = tmp;
	cancel(0, 0);
	return true;
}
