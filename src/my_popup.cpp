#include "my_popup.h"
#include "ressources.h"
#include "control/display/object/image.h"
#include "map_editor.h"
#include "ns_var.h"
#include "ui.hpp"
#include "ui.h"
#include "point.h"
#include "env.hpp"

My_popup::My_popup(void)
{
}

My_popup::~My_popup(void)
{
}

bool	My_popup::init_popupbox(Map_editor* map_editor)
{
	this->__map_editor = map_editor;
	if (Popup_m::init("Size Card", FONT, false) == false)
		return false;
	if (this->add_text_num("width: ", 25, 50) == false)
		return false;
	this->__txt[0] = this->_children.back();
	if (this->add_text_num("height: ", 25, 90) == false)
		return false;
	this->__txt[1] = this->_children.back();
	if (add_button_label(this, "OK", 10, 150, &Map_editor::new_size, this->__map_editor, this->__txt) == false)
		return false;
	if (add_button_label(this, "Cancel", 165, 150, &Map_editor::cancel, this->__map_editor, 0) == false)
		return false;
	return true;
}

bool	My_popup::init_save_and_load_popupbox(Map_editor* map_editor, const char* name, bool (Map_editor::*fct)(Lib2D::Control*, void*))
{
	this->__map_editor = map_editor;
	if (Popup_m::init(name, FONT, false) == false)
		return false;
	if (this->add_text("Name: ", 25, 50) == false)
		return false;
	this->__txt[0] = this->_children.back();
	if (add_button_label(this, "OK", 10, 150, fct, this->__map_editor, this->__txt) == false)
		return false;
	if (add_button_label(this, "Cancel", 165, 150, &Map_editor::cancel, this->__map_editor, 0) == false)
		return false;
	return true;
}

bool	My_popup::add_text_num(const char* txt, int x, int y)
{
	if (add_children(this, create_label(txt, x, y, 25, 0X00000000)) == false)
		return false;
	if (add_children(this, create_txt_box<Lib2D::TextBox_num>(80, 32, x + 100, y, 3))== false)
		return false;
	return true;
}

bool	My_popup::add_text(const char* txt, int x, int y)
{
	if (add_children(this, create_label(txt, x, y, 25, 0X000000000)) == false)
		return false;
	if (add_children(this, create_txt_box<Lib2D::TextBox>(80, 32, x + 100, y, -1))== false)
		return false;
	return true;
}

bool	My_popup::field(Map_editor* map_editor, info_sprite* info)
{
	int			x;
	int			y(0);
	Lib2D::Subimage*	subimage;
	unsigned		i(0);

	this->__map_editor = map_editor;
	if (Popup_m::init("", FONT, false) == false)
		return false;
	while (y < 20)
	{
		x = 0;
		while (x < 19)
		{
			subimage = new (std::nothrow) Lib2D::Subimage;
			if (add_children(this, subimage) == false)
				return false;
			info[i].pos.x = x * 33;
			info[i].pos.y = y * 33;
			info[i].type = FIELD;
			if (Env::get_instance()->ressource.init_subimage_sprite_field(subimage, info[i].pos, 32) == false ||
			    subimage->signals.add(Lib2D::make_func(this->__map_editor, &Map_editor::set_sprite), 0, info + i) == false)
				return false;
			subimage->move(x * 32, y * 32);
			++x;
			++i;
		}
		++y;
	}
	return true;
}

bool	My_popup::ressource(Map_editor* map_editor, info_sprite* info)
{
	Point			sprite;

	this->__map_editor = map_editor;
	if (Popup_m::init("", FONT, false) == false)
		return false;
	if (this->new_ressource(WOOD, 0, 0, info) == false ||
	    this->new_ressource(GOLD, 64, 0, info + 1) == false ||
	    this->new_ressource(STONE,128, 0, info + 2) == false)
		return false;
	return true;
}

bool	My_popup::new_ressource(e_ressource type, int x, int y, info_sprite* info)
{
	Lib2D::Subimage*	subimage;

	info->type = RESSOURCE;
	info->ressource = type;
	subimage = new (std::nothrow) Lib2D::Subimage;
	if (subimage == 0 || add_children(this, subimage) == false)
		return false;
	if (Env::get_instance()->ressource.init_subimage_ressource(subimage, type) == false ||
	    subimage->signals.add(Lib2D::make_func(this->__map_editor, &Map_editor::set_sprite), 0, info) == false)
		return false;
	subimage->move(x, y);
	return true;
}
