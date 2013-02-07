#include "menugame.h"
#include "ressources.h"
#include "game.h"
#include "nation.h"
#include "player.h"
#include "response.h"
#include "env.hpp"
#include "list.hpp"
#include "ui.hpp"
#include "ui.h"



Menugame::Menugame(void):  __nb_land(5), __is_in_game(false), __popup(0)
{
}

Menugame::~Menugame(void)
{
	clear_list(this->__nations);
}

bool	Menugame::init_menugame(void)
{
	Nation*			nation;
	e_land			lands[this->__nb_land];
	int			i = 0;
	t_pos			pos;
	Lib2D::Button_label*	button = 0;

	if (add_children(this, create_bg(MENU, 900, 800)) == false)
		return false;
	if (add_children(this, create_label("Choose Your Nation", 290, 20, 40)) == false)
		return false;
	button = new (std::nothrow) Lib2D::Button_label;
	if (button == 0)
		return false;
	button->resize(50, 100);
	button->move(800, 600);
	if (button->signals.add(Lib2D::make_func(this, &Menugame::print_nation), 0, 0) == false ||
	    button->init_label("Ok", FONT, 20) == false || this->add_child(button) == false)
	{
		delete button;
		return false;
	}
	lands[0] = ENGLAND;
	lands[1] = FRANCE;
	lands[2] = GERMANY;
	lands[3] = JAPAN;
	lands[4] = USA;
	pos.x = 150;
	pos.y = 100;
	while (i < this->__nb_land)
	{
		nation = new (std::nothrow) Nation;
		if (nation == 0)
			return false;
		nation->init_nation(lands[i], pos);
		this->__nations.push_back(nation);
		this->add_child(this->__nations.back()->get_container());
		this->__nations.back()->get_container()->signals.add(Lib2D::make_func(this, &Menugame::choose_nation), 0, this->__nations.back());
		pos.x += 200;
		if (i == 2)
		{
			pos.y += 350;
			pos.x = 250;
		}
		i++;
	}
	return true;
}

bool	Menugame::print_nation(Lib2D::Control*, void*)
{
	Env::get_instance()->client.game_start();
	return true;
}

bool	Menugame::choose_nation(Lib2D::Control*, void* data)
{
	Nation*				nation = (Nation*)data;
	std::list<Nation*>::iterator	it = this->__nations.begin();

	while (it != this->__nations.end())
	{
		(*it)->is_select = false;
		if ((*it)->get_land() == nation->get_land())
		{
			(*it)->is_select = true;
			nation->is_select = true;
			Env::get_instance()->client.send_nation(nation->get_land());
		}
		it++;
	}
	return true;
}

bool	Menugame::derived_treat_render(void)
{
	info_game*	info;

	Env::get_instance()->client.update_data();
	if (this->check_network() == false)
		return false;
	if (this->__is_in_game == true)
		return true;
	info = Env::get_instance()->client.get_msg<info_game>();
	if (info == 0)
		return true;
	if (info->ready == true)
	{
		if (this->create_game(info) == false)
			return false;
	}
	Env::get_instance()->client.remove_buffer_read(info->size);
	return true;
}

bool	Menugame::create_game(info_game* info)
{
	Game*				game(0);
	int				nb(this->children());
	int				nb_player = info->nb_player;
	Player*				player[nb_player + 1];
	int				i = 0;
	std::list<Nation*>::iterator	it;

	while (nb > 0)
	{
		--nb;
		this->del_child(nb);
	}
	while (i < nb_player)
	{
		it = this->__nations.begin();
		while (it != this->__nations.end())
		{
			if (info->player[i].nation == (*it)->get_land())
			{
				player[i] = new (std::nothrow) Player(*it, i);
				if (player[i] == 0)
					return false;
				break;
			}
			it++;
		}
		if (it == this->__nations.end())
			return false;
		i++;
	}
	player[i] = 0;
	game = new (std::nothrow) Game;
	if (game == 0 || game->Init_game(player, info->id_player) == false || this->add_child(game) == false)
	{
		delete game;
		return false;
	}
	this->__is_in_game = true;
	return true;
}

bool	Menugame::create_popup(const char* title)
{
	Env::get_instance()->client.clear();
	if (this->__popup != 0)
		return true;
	this->__popup = new (std::nothrow) Lib2D::Popup_m;
	if (this->__popup == 0)
		return false;
	if (add_children(this, this->__popup) == false)
	{
		this->__popup = NULL;
		return false;
	}
	this->__popup->resize(250, 250);
	this->__popup->move(175, 175);
	if (this->__popup->init(title, FONT, false) == false ||
	    add_button_label(this->__popup, "Ok", 60, 70, &Menugame::change_context, this, 0) == false)
	{
		this->__popup = NULL;
		return false;
	}
	return true;
}

bool	Menugame::change_context(Lib2D::Control*, void*)
{
	Lib2D::Window::get_instance()->context(0);
	return true;
}

bool	Menugame::check_network(void)
{
	char	data[100];
	msg*	ret_server;

	*data = 0;
	if (this->__popup != 0)
		return true;
	ret_server = Env::get_instance()->client.get_msg<msg>();
	if (ret_server != 0)
	{
		ret_server->get_msg(data);
		return this->create_popup(data);
	}
	else if (Env::get_instance()->client.is_run() == false)
		return this->create_popup("connection lost");
	return true;
}

void	Menugame::delete_popup(void)
{
	if (this->__popup != 0)
	{
		this->del_child(this->__popup);
		this->__popup = 0;
	}
}
