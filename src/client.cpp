#include "client.h"
#include "tools.h"
#include "response.h"
#include <netdb.h>
#include <iostream>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <dlfcn.h>

Client::Client(void)
{
}

Client::~Client(void)
{
}

bool	Client::alloc_buffer(void)
{
	if (this->__buf_write.init(SIZE_BUFFER_WRITE) == false)
		return false;
	if (this->__buf_read.init(SIZE_BUFFER_READ) == false)
		return false;
	return true;
}

bool	Client::init(const char* port, const char* ip)
{
	if (Network::init(port, ip) == false)
		return this->clear();
	if (connect(this->_sockfd, this->_res->ai_addr, this->_res->ai_addrlen) == -1)
		return this->clear();
	if (this->alloc_buffer() == false)
		return this->clear();
	Network::set_init(true);
	return true;
}

bool	Client::write(void)
{
	int	nsend;

	nsend = send(this->_sockfd, this->__buf_write.get_data(), this->__buf_write.get_size(), MSG_NOSIGNAL);
	if (nsend > 0)
	{
		this->__buf_write.remove(nsend);
		return true;
	}
	return false;
}

bool	Client::read(void)
{
	char	buf[SIZE_BUFFER_READ];
	int	nrecv;

	nrecv = recv(this->_sockfd, buf, SIZE_BUFFER_READ, MSG_NOSIGNAL);
	if (nrecv < 1)
		return false;
	if (this->__buf_read.get_size() + nrecv > this->__buf_read.get_capacity())
		return false;
	this->__buf_read.addstr(buf, nrecv);
	return true;
}

bool	Client::run(void)
{
	bool	ret(true);
	fd_set	fdsr;
	fd_set	fdsw;

	if (Network::is_run() == false)
		return false;
	this->init_fd(&fdsr, &fdsw);
	while (select(this->_sockfd + 1, &fdsr, &fdsw, 0, 0) >= 0 &&
	       Network::is_run() == true && ret == true)
	{
		if (FD_ISSET(this->_sockfd, &fdsw))
			ret = this->write();
		else if (FD_ISSET(this->_sockfd, &fdsr))
			ret = this->read();
		if (ret == false)
			break;
		this->init_fd(&fdsr, &fdsw);
	}
	return this->clear();
}

bool		Client::add_buffer(const char* str, unsigned int size)
{
	return this->__buf_write.addstr(str, size) == size;
}

bool		Client::clear(void)
{
	Network::clear();
	this->__buf_write.clear();
	this->__buf_read.clear();
	return false;
}

void	Client::init_fd(fd_set* fdsr, fd_set* fdsw)
{
	FD_ZERO(fdsw);
	FD_ZERO(fdsr);
	if (this->__buf_write.is_empty() == false)
		FD_SET(this->_sockfd, fdsw);
	else
		FD_SET(this->_sockfd, fdsr);
}

void	Client::remove_buffer_read(unsigned int size)
{
	this->__buf_read.remove(size);
}

bool	Client::send_nation(const e_land land)
{
	nation	msg;

	msg.id_nation = land;
	return this->send_to_server(&msg);
}

bool	Client::game_start(void)
{
	info_struct	msg(LAUNCH_GAME);

	return this->send_to_server(&msg);
}

bool	Client::send_to_server(const info_struct* msg)
{
	return this->__buf_write.addstr((char*)msg, msg->size) == msg->size;
}

bool	Client::update_data(void)
{
	fd_set	fdsr;
	fd_set	fdsw;
	timeval	timeout;

	Network::init_timeout(timeout);
	if (Network::is_run() == false)
		return true;
	this->init_fd(&fdsr, &fdsw);
	if (select(this->_sockfd + 1, &fdsr, &fdsw, 0, &timeout)  >= 0)
	{
		if (FD_ISSET(this->_sockfd, &fdsw))
			this->write();
		else if (FD_ISSET(this->_sockfd, &fdsr))
			this->read();
	}
	return true;
}

bool	Client::send_building(const Point& pos, e_type type, int player)
{
	info_building	msg;

	msg.pos = pos;
	msg.id_build = type;
	msg.player = player;
	return this->send_to_server(&msg);
}

bool	Client::send_unit(int id_building, int id_player, int nb_product)
{
	info_units	msg;

	msg.id_building = id_building;
	msg.nb_product = nb_product;
	msg.id_player = id_player;
	return this->send_to_server(&msg);
}


bool	Client::unit_move(const Point& dest, unsigned id_unit, unsigned id_player)
{
	units_move	msg;

	msg.pos = dest;
	msg.id_unit = id_unit;
	msg.id_player = id_player;
	return this->send_to_server(&msg);
}

bool	Client::unit_attack(int id_player_attack, int id_player_attacked, int id_unit_attacked, int hp_to_remove, type_info info)
{
	units_attack	msg;

	msg.hp_to_remove = hp_to_remove;
	msg.id_player_attack = id_player_attack;
	msg.id_player_attacked = id_player_attacked;
	msg.id_unit_attacked = id_unit_attacked;
	msg.info = info;
	return this->send_to_server(&msg);
}

bool	Client::player_wins(int id_player)
{
	msg	message;

	message.id_msg = PLAYER_WIN;
	message.data = id_player;
	return this->send_to_server(&message);
}
