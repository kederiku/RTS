#include "my_popup.h"
#include "ressources.h"
#include "control/display/object/image.h"
#include "map_editor.h"
#include "ns_var.h"
#include "ui.hpp"
#include "ui.h"
#include "point.h"

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
	Lib2D::TextBox_num*	text_box;
	Lib2D::Label*		label;

	label =  new (std::nothrow) Lib2D::Label;
	if (label == 0)
		return false;
	label->move(x, y);
	if (label->init(txt, FONT, 25, 0X00000000) == false || this->add_child(label) == false)
	{
		delete label;
		return false;
	}
	text_box = new (std::nothrow) Lib2D::TextBox_num;
	if (text_box == 0)
	{
		delete label;
		return false;
	}
	text_box->resize(80, 32);
	text_box->move( x + 100, y);
	if (text_box->init(FONT, 32, 3, 0xFFFFFFFF, true) == false || this->add_child(text_box) == false)
	{
		delete label;
		delete text_box;
		return false;
	}
	return true;
}

bool	My_popup::add_text(const char* txt, int x, int y)
{
	Lib2D::TextBox*		text_box;
	Lib2D::Label*		label;

	label =  new (std::nothrow) Lib2D::Label;
	if (label == 0)
		return false;
	label->move(x, y);
	if (label->init(txt, FONT, 25, 0X00000000) == false || this->add_child(label) == false)
	{
		delete label;
		return false;
	}
	text_box = new (std::nothrow) Lib2D::TextBox;
	if (text_box == 0)
	{
		delete label;
		return false;
	}
	text_box->resize(80, 32);
	text_box->move(x + 100, y);
	if (text_box->init(FONT, 32, -1, 0xFFFFFFFF, true) == false || this->add_child(text_box) == false)
	{
		delete label;
		delete text_box;
		return false;
	}
	return true;
}

bool	My_popup::create_sprite(Map_editor* map_editor, const std::list<info_img>& img)
{
	std::list<info_img>::const_iterator	it(img.begin());
	std::list<info_img>::const_iterator	it_end(img.end());
	Lib2D::Image*				source;
	Lib2D::Image*				tmp;
	int					width(0);
	int					height(0);

	if (img.size() < 3)
		return false;
	this->__map_editor = map_editor;
	source = img.front().img_complete;
	while (it != it_end)
	{
		tmp = source->get_image_part(it->sprite_pos.x, it->sprite_pos.y, it->sprite_size.x, it->sprite_size.y);
		if (it->sprite_pos.x + it->sprite_size.x > width)
			width = it->sprite_pos.x + it->sprite_size.x;
		if (it->sprite_pos.y + it->sprite_size.y > height)
			height = it->sprite_pos.y + it->sprite_size.y;
		if (tmp == 0)
			return false;
		tmp->resize(it->img_size.x, it->img_size.y);
		tmp->move(it->sprite_pos.x, it->sprite_pos.y);
		if (this->add_child(tmp) == 0)
		{
			delete tmp;
			return false;
		}
		if (tmp->signals.add(Lib2D::make_func(this->__map_editor, &Map_editor::set_sprite), 0, (void*)&(*it)) == false)
			return false;
		++it;
	}
	this->resize(width, height);
	if (Popup_m::init("", FONT, false) == false)
		return false;
	return true;
}
