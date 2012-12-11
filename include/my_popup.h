#ifndef _MY_POPUP_H_
#define _MY_POPUP_H_

#include "control/display/multi/popup_m.h"
#include "control/display/object/image.h"
#include "control/display/mono/textbox_num.h"
#include "info_img.h"
class	Map_editor;
class	Point;
class	TextBox_num;


class	My_popup: public Lib2D::Popup_m
{
	Lib2D::Control*	__txt[2];
	Map_editor*	__map_editor;
	bool		add_text_num(const char* txt, int x, int y);
	bool		add_text(const char* txt, int x, int y);
	void		init_info_img(info_img* info, int x, int y, int width, int height);
public:
	My_popup(void);
	virtual ~My_popup(void);

	bool	create_sprite(Map_editor* map_editor, const std::list<info_img>& img);
	bool	init(Lib2D::Image* img, Map_editor* map_editor, int size_w, int size_h);
	bool	clear(Lib2D::Control* ctrl, void* data);
	bool	init_popupbox(Map_editor* map_editor);
	bool	init_save_and_load_popupbox(Map_editor* map_editor, const char*,
		bool (Map_editor::*fct)(Lib2D::Control*, void*));
	bool	ressource(Lib2D::Image* img, Map_editor* map_editor_h);
};

#endif
