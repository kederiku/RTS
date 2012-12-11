#include "server.h"
#include "user.h"
#include "list.hpp"
#include "response.h"
#include <netdb.h>

Server::Server(void)
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
		{
			ret = (*it)->read();
//			std::cout << "lecture " <<  (int) ret << std::endl;
		}
		else if (FD_ISSET((*it)->get_fd(), fdsw))
		{
			ret = (*it)->write();
//			std::cout << "ecriture " <<  (int) ret << std::endl;

		}
		if (ret == false || this->close_client(*it) == true || this->parser_buffer(*it) == false)
		{
//			std::cout << "on delete le client ici, et pas ailleur" << std::endl;
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

void	Server::send_message(const info_struct* msg)
{
	std::list<User*>::iterator	it(this->__client.begin());
	std::list<User*>::iterator	it_end(this->__client.end());

	while (it != it_end)
	{
		if ((*it)->get_error() == 0)
			if ((*it)->add_buffer((char*)msg, msg->size) == false)
				std::cout << "error add buffer 1" << std::endl;
		++it;
	}
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
			this->choose_nation(user);
			break;
		case LAUNCH_GAME:
			this->update_statut_game();
			break;
		default:
			return false;
	}
	user->rmv_buffer(info->size);
	return true;
}

bool	Server::choose_nation(User* user)
{
	nation*	data(Network::get_msg<nation>(user->get_buf_read()));

	if (data == 0)
		return true;
	user->set_nation(data->id_nation);
	return true;
}


bool	Server::update_statut_game(void)
{
	info_game			msg;
	std::list<User*>::iterator	it(this->__client.begin());
	std::list<User*>::iterator	it_end(this->__client.end());
	unsigned			i(0);

	while (it != it_end && (*it)->is_ready_to_play() == true)
	{
		msg.player[i].nation = (*it)->get_nation();
		msg.player[i].pos = 0;
		++it;
		++i;
	}
	msg.ready = (it == it_end);
	msg.nb_player = this->__nb_player_max;
	this->send_message(&msg);
	return true;
}


bool	Server::close_client(User* user) const
{
	if (user->get_error() == 0)
		return false;
	if (user->get_buf_write().is_empty() == false)
		return false;
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
