#include "network.h"
#include "tools.h"
#include <netdb.h>
#include <unistd.h>
#include <network.hpp>

void*	fct_run(void* data)
{
	Network*	net;

	net = (Network*)data;
	net->run();
	return 0;
}

Network::Network(void): __threads(0), __init(false), _res(0), _sockfd(-1)
{
}

Network::~Network(void)
{
	this->clear();
}

bool	Network::init(const char* port, const char* ip)
{
	addrinfo	hints;

	if (this->__init == true)
		return this->clear();
	id::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(ip, port, &hints, &this->_res) != 0)
		return this->clear();
	this->_sockfd = socket(this->_res->ai_family, this->_res->ai_socktype,
			        this->_res->ai_protocol);
	if (this->_sockfd == -1)
		return this->clear();
	return true;
}

bool	Network::clear(void)
{
	this->__init = false;
	if (this->__threads != 0)
		pthread_join(*this->__threads, 0);
	freeaddrinfo(this->_res);
	if (this->_sockfd != -1)
		close(this->_sockfd);
	this->_res = 0;
	this->_sockfd = -1;
	return false;
}

bool	Network::is_run(void) const
{
	return this->__init;
}

void	Network::quit(void)
{
	this->__init = false;
}

bool	Network::create_thread(void)
{
	this->__threads = new (std::nothrow) pthread_t;
	if (this->__threads == 0)
		return false;
	if (pthread_create(this->__threads, NULL, &::fct_run, this) == 0)
	{
		this->__init = true;
		return true;
	}
	else
		return false;
}

void	Network::init_timeout(timeval& timeout)
{
	timeout.tv_sec = 0;
	timeout.tv_usec = 500;
}

void	Network::set_init(bool init)
{
	this->__init = init;
}
