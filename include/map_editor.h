#ifndef _MAP__EDITOR_H_
#define _MAP__EDITOR_H_

#include <iostream>
#include <stdlib.h>
#include "point.h"
#include "enums.h"
#include <Lib2D.h>
#include "my_popup.h"
#include "map.h"
#include "info_img.h"
class	Container_game;

class	Map_editor : public Lib2D::Container
{
	Container_game*		__container_map;
	bool			__init;
	Lib2D::Image		__sprite_field;
	Lib2D::Image		__sprite_ressource;
	My_popup*		__popup;
	Lib2D::Image*		__sprite_img;
	info_img		__pos_img;
	std::list<info_img>	__sprite_popup;

	bool	add_sprite(const Lib2D::s_mouse_event* mouse_event);
	bool	add_sprite_info(info_img& add);
	void	init_info_img(info_img* info, int pos_x, int pos_y, int sprite_w, int sprite_h, int img_w, int img_h);
	bool	create_popup_sprite(void);
	bool	move_sprite(const Lib2D::s_mouse_event* mouse_event);
public:
	Map_editor(void);
	virtual ~Map_editor(void);

	bool	init_buttons(void);
	bool	create_popup_field(Lib2D::Control* , void*);
	bool	create_popup_ressource(Lib2D::Control* , void*);
	bool	create_popup_new_map(Lib2D::Control*, void*);
	bool	save_map(Lib2D::Control*, void*);
	bool	save_file(Lib2D::Control*, void* data);
	bool	load_map(Lib2D::Control*, void*);
	bool	load_file(Lib2D::Control*, void* data);
	bool	cancel(Lib2D::Control*, void*);
	bool	is_popup_open(void);
	bool	is_in_container_map(const Lib2D::s_mouse_event* mouse_event) const;
	bool	derived_treat_event(Lib2D::Event* event);
	bool	init(void);
	bool	new_size(Lib2D::Control*, void* data);
	bool	set_sprite(Lib2D::Control*, void* data);
};

#endif
