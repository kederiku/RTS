#include <Lib2D.h>
#include "ressources.h"

template <typename T>
Lib2D::Button_label*	create_button_label(const char* txt, int x, int y,
					    bool(T::*fct)(Lib2D::Control*, void*), T* class_instance, void* data)
{
	Lib2D::Button_label*	ret(0);

	ret = new (std::nothrow) Lib2D::Button_label;
	if (ret == 0)
		return 0;
	ret->move(x, y);
	ret->resize(150, 40);
	if (ret->init_label(txt, FONT, 16, 0xFFFFFFFF) == false ||
	    ret->signals.add(Lib2D::make_func(class_instance, fct), 0, data) == false)
	{
		delete ret;
		return 0;
	}
	ret->set_background(0x007FFFFF);
	return ret;
}

template <typename T, typename U>
bool	add_button_label(U ctx, const char* txt, int x, int y,
			 bool(T::*fct)(Lib2D::Control*, void*), T* class_instance, void* data, bool visible = true)
{
	Lib2D::Button_label*	button;

	button = create_button_label(txt, x, y, fct, class_instance, data);
	if (button == 0 || ctx->add_child(button) == false)
	{
		delete  button;
		return false;
	}
	button->visible(visible);
	return true;
}


template <typename T, typename U>
bool	add_children(T& parent, U child, bool first = false)
{
	if (child == 0)
		return false;
	if (first == true)
	{
		if (parent->add_child(child, 0) == false)
		{
			delete child;
			return false;
		}
	}
	else
	{
		if (parent->add_child(child) == false)
		{
			delete child;
			return false;
		}
	}
	return true;
}

template <typename T>
T*	create_txt_box(int width, int height, int x, int y, int max_char)
{
	T*	ret(new (std::nothrow)T);

	if (ret == 0)
		return 0;
	ret->resize(width, height);
	ret->move(x, y);
	if (ret->init(FONT, 32, max_char) == false)
	{
		delete ret;
		return 0;
	}
	return ret;
}

/*
template <typename T, typename U>
bool	add_signals(bool(U::*fct)(Lib2D::Control*, void*), U* class_instance, void* data)
{
	return T->signals.add(Lib2D::make_func(class_instance, fct), 0, data);
}
*/
