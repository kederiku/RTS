#ifndef __CONNECTION__H_
#define __CONNECTION__H_

#include <Lib2D.h>
#include <ns_var.h>
#include <pthread.h>
#include "control/display/multi/popup_m.h"

class Connection
{
public:
	Connection(void);
	~Connection(void);
	bool		Setting_Connection(bool create);
	Lib2D::Context*	Get_Context_Create(void);
	Lib2D::Context*	Get_Context_Join(void);
	bool		Add_child_to_context(Lib2D::Context*);
	void		Del_child_to_context(Lib2D::Context*);
	bool		Delete_Child(Lib2D::Control* control, void* data);
	bool		Get_Value(Lib2D::Control* control, void* data);
	bool		Init(void);
	bool		create_server(void);
	bool		join_server(void);

private:

	Lib2D::TextBox*		__box_adress;
	Lib2D::TextBox_num*	__box_port;
	Lib2D::TextBox_num*	__box_nb_player;
	Lib2D::Label_link*	__link_return;
	Lib2D::Button_label*	__button_label_send;
	Lib2D::Context*		__context_create;
	Lib2D::Context*		__context_join;
	bool			__create;
	Lib2D::Popup_m*		__popup;
	Lib2D::Context*		__context_popup;

	bool		create_popup(Lib2D::Context* ctx, const char* title);
	bool		del_popup(Lib2D::Control* ctrl, void* data);
};

#endif
