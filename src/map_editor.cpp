#include "map_editor.h"
#include "ressources.h"
#include "point.h"
#include "ui.hpp"
#include "ns_var.h"
#include "container_game.h"

Map_editor::Map_editor(void):
	__container_map(0),
	__init(false),
	__popup(0),
	__sprite_img(0)
{
	this->__pos_img.img_complete = 0;
}

Map_editor::~Map_editor(void)
{
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
//	if (add_button_label(this, "Add Collision", 450, y, &Map_editor::create_popup_field, this, 0) == false)
//		return false;
	if (add_button_label(this, "Save", 600, y, &Map_editor::save_map, this, 0) == false)
		return false;
	if (add_button_label(this, "Load", 750, y, &Map_editor::load_map, this, 0) == false)
		return false;
	this->__init = true;
	return true;
}

bool	Map_editor::add_sprite_info(info_img& add)
{
	try
	{
		this->__sprite_popup.push_back(add);
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}

void	Map_editor::init_info_img(info_img* info, int pos_x, int pos_y, int sprite_w, int sprite_h, int img_w, int img_h)
{
	info->sprite_pos.x = pos_x;
	info->sprite_pos.y = pos_y;
	info->sprite_size.x = sprite_w;
	info->sprite_size.y = sprite_h;
	info->img_size.x = img_w;
	info->img_size.y = img_h;
}

bool	Map_editor::create_popup_field(Lib2D::Control* , void*)
{
	int		x;
	int		y(0);
	info_img	add;

	if (this->is_popup_open() == true)
		return true;
	this->__sprite_popup.clear();
	add.img_complete = &this->__sprite_field;
	while (y < 20)
	{
		x = 0;
		while (x < 19)
		{
			this->init_info_img(&add, x * 33, y * 33, 32, 32, 32, 32);
			if (this->add_sprite_info(add) == false)
				return false;
			++x;
		}
		++y;
	}
	if (this->create_popup_sprite() == false)
		return false;
	return true;
}


bool	Map_editor::create_popup_ressource(Lib2D::Control* , void*)
{
	info_img	add;

	if (this->is_popup_open() == true)
		return true;
	add.img_complete = &this->__sprite_ressource;
	this->__sprite_popup.clear();
	this->init_info_img(&add, 0, 0, 97, 180, 64, 96);
	if (this->add_sprite_info(add) == false)
		return false;
	this->init_info_img(&add, 99, 0, 90, 77, 64, 64);
	if (this->add_sprite_info(add) == false)
		return false;
	this->init_info_img(&add, 195, 0, 73, 75, 64, 64);
	if (this->add_sprite_info(add) == false)
		return false;
	if (this->create_popup_sprite() == false)
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
	if (this->__popup->init_popupbox(this) == false || this->add_child(this->__popup) == false)
	{
		delete this->__popup;
		this->__popup = 0;
		return false;
	}
	return true;
}

bool	Map_editor::create_popup_sprite(void)
{
	if (this->__sprite_img != 0)
		Multi::del_child(this->__sprite_img);
	this->__sprite_img = 0;
	this->__popup = new (std::nothrow) My_popup;
	if (this->__popup == 0)
		return false;
	this->__popup->resize(300, 200);
	this->__popup->move(175, 75);
	if (this->__popup->create_sprite(this, this->__sprite_popup) == false || this->add_child(this->__popup) == false)
	{
		delete this->__popup;
		this->__popup = 0;
		return false;
	}
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
	{
		std::cout << "save fail" << std::endl;
		return false;
	}
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


	this->del_child(this->__container_map);
	this->__container_map = new (std::nothrow) Container_game;
	if (this->__container_map == 0 || this->__container_map->init(path) == false ||
	    this->add_child(this->__container_map) == false)
	{
		delete this->__container_map;
		this->__container_map = 0;
		return false;
	}
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
	if (this->__pos_img.img_complete == &this->__sprite_field)
		return  this->__container_map->add_field(this->__pos_img, pos);
	else if (this->__pos_img.img_complete == &this->__sprite_ressource)
		return  this->__container_map->add_ressource(this->__pos_img, pos);
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
	if (this->__init == true)
		return true;
	if (Container::init() == false)
		return false;
	this->__container_map = new (std::nothrow) Container_game;
	if (this->__container_map == 0)
		return false;
	if (this->__container_map->init(25, 25) == false || this->add_child(this->__container_map) == false)
	{
		delete this->__container_map;
		return false;
	}
	if (this->__sprite_field.load_bmp(MAP) == false)
		return false;
	if (this->__sprite_ressource.load_bmp(RES) == false)
		return false;
	if (this->init_buttons() == false)
		return false;
	this->__init = true;
	return true;
}


bool	Map_editor::new_size(Lib2D::Control*, void* data)
{
	Lib2D::TextBox_num**	txt((Lib2D::TextBox_num**)data);
	int			width(ns_cmc::ns_var::f_atoi(txt[0]->get_value()));
	int			height(ns_cmc::ns_var::f_atoi(txt[1]->get_value()));

	if (this->__container_map == 0)
		return false;
	if (width != 0 && height != 0)
	{
		this->del_child(this->__container_map);
		this->__container_map = new (std::nothrow) Container_game;
		if (this->__container_map == 0)
			return false;
		if (this->__container_map->init(width, height) == false || this->add_child(this->__container_map) == false)
		{
			delete this->__container_map;
			return false;
		}
	}
	cancel(0, 0);
	return true;
}


bool	Map_editor::set_sprite(Lib2D::Control*, void* data)
{
	info_img*		info((info_img*)data);
	Lib2D::Image*		tmp;

	if (this->__container_map == 0 ||  this->__pos_img == *info)
		return true;
	tmp = info->img_complete->get_image_part(info->sprite_pos.x, info->sprite_pos.y, info->sprite_size.x, info->sprite_size.y);
	if (tmp == 0)
		return false;
	tmp->resize(info->img_size.x, info->img_size.y);
	if (this->add_child(tmp) == 0)
	{
		delete tmp;
		return false;
	}
	tmp->visible(false);
	this->__pos_img = *info;
	this->__sprite_img = tmp;
	cancel(0, 0);
	return true;
}
