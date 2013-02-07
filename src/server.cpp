#include "server.h"
#include "list.hpp"
#include "response.h"
#include <netdb.h>

Server::Server(void): __tick(0)
{
}

Server::~Server(void)
{
	this->clear();
}

bool	Server::init(const char* port, const char* ip, unsigned nb_player)
{
	if (Network::init(port, ip) == false)
		return this->clear();
	if (bind(this->_sockfd, this->_res->ai_addr, this->_res->ai_addrlen) == -1)
		return this->clear();
	if (listen(this->_sockfd, 10) == -1)
		return this->clear();
	if (Network::create_thread() == false)
		return this->clear();
	this->__nb_player_max = nb_player;
	this->__game_start = false;
	return true;
}

bool	Server::clear(void)
{
	Network::clear();
	clear_list(this->__client);
	return false;
}

bool	Server::add_client(int& fd_max)
{
	User*				client;
	std::list<User*>::iterator	it(this->__client.begin());
	std::list<User*>::iterator	it_end(this->__client.end());

	try
	{
		client = new User();
		if (client->init(this->_sockfd) == false)
		{
			delete client;
			return false;
		}
		if (this->__game_start == true)
		{
			this->send_msg(client, GAME_ALREADY_START);
			client->set_error(1);
		}
		if (this->__client.size() + 1 > this->__nb_player_max)
		{
			this->send_msg(client, GAME_FULL);
			client->set_error(1);
		}
		while (it != it_end && client->get_fd() > (*it)->get_fd())
			++it;
		this->__client.insert(it, client);
		if (it == it_end)
			fd_max = client->get_fd() + 1;
	}
	catch (std::exception ex)
	{
		delete client;
		return false;
	}
	return true;
}

void	Server::init_fd(fd_set* fdsr, fd_set* fdsw)
{
	std::list<User*>::iterator	it(this->__client.begin());
	std::list<User*>::iterator	it_end(this->__client.end());

	FD_ZERO(fdsw);
	FD_ZERO(fdsr);
	FD_SET(this->_sockfd, fdsr);
	while (it != it_end)
	{
		if ((*it)->get_buf_write().is_empty() == false)
			FD_SET((*it)->get_fd(), fdsw);
		else
			FD_SET((*it)->get_fd(), fdsr);
		++it;
	}
}

void	Server::check_fd(fd_set* fdsr, fd_set* fdsw, int& fd_max)
{
	std::list<User*>::iterator	it(this->__client.begin());
	bool				ret;

	while (it != this->__client.end())
	{
		ret = true;
		if (FD_ISSET((*it)->get_fd(), fdsr))
			ret = (*it)->read();
		else if (FD_ISSET((*it)->get_fd(), fdsw))
			ret = (*it)->write();
		if (ret == false || this->close_client(*it) == true || this->parser_buffer(*it) == false)
		{
			if (it == this->__client.end())
				fd_max = this->__client.back()->get_fd() + 1;
			delete *it;
			it = this->__client.erase(it);
		}
		else
			++it;
	}
}

bool	Server::run(void)
{
	fd_set	fdsr;
	fd_set	fdsw;
	int	fd_max;
	timeval	timeout;

	if (Network::is_run() == false)
		return false;
	Network::init_timeout(timeout);
	fd_max = this->_sockfd + 1;
	this->init_fd(&fdsr, &fdsw);
	while (select(fd_max, &fdsr, &fdsw, 0, &timeout) >= 0 && Network::is_run() == true)
	{
		if (FD_ISSET(this->_sockfd, &fdsr) == true)
		{
			if (this->add_client(fd_max) == false)
				return false;
		}
		this->check_fd(&fdsr, &fdsw, fd_max);
		this->init_fd(&fdsr, &fdsw);
		Network::init_timeout(timeout);
	}
	return true;
}

bool	Server::parser_buffer(User* user)
{
	info_struct*	info;

	if (user->get_buf_read().get_size() < sizeof(info_struct))
		return true;
	info = (info_struct*)user->get_buf_read().get_data();
	if (user->get_buf_read().get_size() < info->size)
		return true;
	switch (info->type)
	{
		case NATION:
			if (this->choose_nation(user) == false)
				return true;
			break;
		case LAUNCH_GAME:
			if (this->update_statut_game() == false)
				return true;
			break;
		case NEW_BUILDING:
			if (this->send_to_all_player<info_building>(user) == false)
				return true;
			break;
		case NEW_UNIT:
			if (this->send_to_all_player<info_units>(user) == false)
				return true;
			break;
		case UNIT_MOVE:
			if (this->send_to_all_player<units_move>(user) == false)
				return true;
			break;
		case UNIT_ATTACK:
			if (this->send_to_all_player<units_attack>(user) == false)
				return true;
			break;
		case MSG:
			if (this->send_to_all_player<msg>(user) == false)
				return true;
			break;
		default:
			return false;
	}
	user->rmv_buffer(info->size);
	return true;
}

void	Server::add_buffer_client(const info_struct* msg, int id)
{
	std::list<User*>::iterator	it(this->__client.begin());
	std::list<User*>::iterator	it_end(this->__client.end());

	while (it != it_end)
	{
		if ((*it)->get_error() == 0 || (*it)->get_fd() != id)
			if ((*it)->add_buffer((char*)msg, msg->size) == false)
				std::cout << "error add buffer 1" << std::endl;
		++it;
	}
}

bool	Server::close_client(User* user) const
{
	if (user->get_error() == 0)
		return false;
	if (user->get_buf_write().is_empty() == false)
		return false;
	return true;
}

bool	Server::choose_nation(User* user)
{
	nation*	data(Network::get_msg<nation>(user->get_buf_read()));

	if (data == 0)
		return false;
	user->set_nation(data->id_nation);
	return true;
}


bool	Server::update_statut_game(void)
{
	info_game			msg;
	std::list<User*>::iterator	it(this->__client.begin());
	std::list<User*>::iterator	it_end(this->__client.end());
	unsigned			i(0);

	if (this->__client.size() != this->__nb_player_max)
		return true;
	while (it != it_end)
	{
		if ((*it)->is_ready_to_play() == true)
		{
			msg.player[i].nation = (*it)->get_nation();
			++i;
		}
		else if ((*it)->get_error() == 0)
			return true;
		++it;
	}
	if (i != this->__nb_player_max)
		return true;
	this->__game_start = true;
	msg.ready = true;
	msg.nb_player = i;
	msg.size += sizeof(*(msg.player)) * i;
	it = this->__client.begin();
	i = 0;
	while (it != it_end)
	{
		if ((*it)->is_ready_to_play())
		{
			msg.id_player = i;
			if ((*it)->add_buffer((char*)&msg, msg.size) == false)
				std::cout << "error add buffer 3" << std::endl;
			++i;
		}
		++it;
	}
	return true;
}

void	Server::send_msg(User* user, msg_type type, int data)
{
	msg	to_send;

	to_send.id_msg = type;
	to_send.data = data;
	if (user->add_buffer((char*)&to_send, to_send.size) == false)
		std::cout << "error add buffer 2" << std::endl;
}

bool	Server::send_info_player(int id_player)
{
	info_player			data(id_player);
	std::list<User*>::iterator	it(this->__client.begin());
	std::list<User*>::iterator	it_end(this->__client.end());

	while (it != it_end)
	{
		if ((*it)->get_fd() != id_player && (*it)->get_error() != 0)
		{
			data.player[data.nb_player] = (*it)->get_fd();
			++data.nb_player;
		}
		++it;
	}
	data.size += data.nb_player;
	this->add_buffer_client(&data);
	return true;
}

bool	Server::check_tick(int tick) const
{
	std::list<User*>::const_iterator	it(this->__client.begin());
	std::list<User*>::const_iterator	it_end(this->__client.end());

	while (it != it_end)
	{
		if ((*it)->get_tick() != tick)
			return false;
		++it;
	}
	return true;
}

void	Server::set_tick(int tick)
{
	std::list<User*>::iterator	it(this->__client.begin());
	std::list<User*>::iterator	it_end(this->__client.end());

	while (it != it_end)
	{
		(*it)->set_tick(tick);
		++it;
	}
}
