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
//	std::cout << "init network succes" << std::endl;
	if (connect(this->_sockfd, this->_res->ai_addr, this->_res->ai_addrlen) == -1)
		return this->clear();
//	std::cout << "connect succes" << std::endl;
	if (this->alloc_buffer() == false)
		return this->clear();
//	std::cout << "alloc buffer succes" << std::endl;
	Network::set_init(true);
	return true;
}

bool	Client::write(void)
{
	int	nsend;

	if (this->__buf_write.is_empty() == true)
		return true;
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
	{
//		std::cout << "j ai rien recu, c est pas normal" << std::endl;
		return false;
	}
	if (this->__buf_read.get_size() + nrecv > this->__buf_read.get_capacity())
	{
//		std::cout << "tu rempli trop tom buffer" << std::endl;
//		std::cout << "buffer space " << this->__buf_read.get_space() << std::endl;
//		std::cout << "donnee recu " << nrecv << std::endl;
//		std::cout << "buffer capa " << this->__buf_read.get_capacity() << std::endl;
//		std::cout << "buffer size " << this->__buf_read.get_size() << std::endl;
		return false;
	}
//	std::cout << "le serveur ma envoyer des chose " << nrecv << std::endl;
	this->__buf_read.addstr(buf, nrecv);
	return true;
}

bool	Client::run(void)
{
	bool	ret(true);
	fd_set	fdsr;
	fd_set	fdsw;
	timeval	timeout;

	Network::init_timeout(timeout);
	if (Network::is_run() == false)
		return false;
	this->init_fd(&fdsr, &fdsw);
	while (select(this->_sockfd + 1, &fdsr, &fdsw, 0, &timeout)  >= 0 &&
	       Network::is_run() == true && ret == true)
	{
		if (FD_ISSET(this->_sockfd, &fdsw))
		{
			ret = this->write();
//			if (ret == false)
//				std::cout << "je sais pas ecrire" << std::endl;
		}
		else if (FD_ISSET(this->_sockfd, &fdsr))
		{
			ret = this->read();
//			if (ret == false)
//				std::cout << "je sais pas lire" << std::endl;
		}
		if (ret == false)
			break;
		this->init_fd(&fdsr, &fdsw);
		Network::init_timeout(timeout);
	}
	return this->clear();
}

bool		Client::add_buffer(const char* str, unsigned int size)
{
	return this->__buf_write.addstr(str, size) == size;
}

bool		Client::clear(void)
{
	std::cout << "client clear" << std::endl;
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
