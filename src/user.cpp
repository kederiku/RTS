#include "user.h"
#include "response.h"
#include <sys/socket.h>

User::User(void): __fd(-1), __land(OTHER), __error(0)
{
	this->__timeout.start();
}

User::~User(void)
{
//	std::cout << "repose en paix "  << this->__fd << std::endl;
	if (this->__fd != -1)
		close(this->__fd);
}

bool	User::init(const int& sckfd)
{
	socklen_t	addr_len;
	sockaddr	sockaddr;

	if (this->__buf_write.init(SIZE_WRITE) == false)
		return false;
	if (this->__buf_read.init(SIZE_READ) == false)
		return false;
	addr_len = sizeof(sockaddr);
	this->__fd = accept(sckfd, &sockaddr, &addr_len);
	if (this->__fd == -1)
		return false;
//	std::cout << "bienvenue "  << this->__fd << std::endl;
	return true;
}

int	User::get_fd(void) const
{
	return this->__fd;
}

const Buffer&	User::get_buf_read(void) const
{
	return this->__buf_read;
}

const Buffer&	User::get_buf_write(void) const
{
	return this->__buf_write;
}

bool		User::write(void)
{
	int	nsend;

	nsend = send(this->__fd, this->__buf_write.get_data(), this->__buf_write.get_size(), MSG_NOSIGNAL);
	if (nsend > 0)
	{
		this->__buf_write.remove(nsend);
		return true;
	}
	return false;
}

bool	User::read(void)
{
	char	buf[SIZE_READ];
	int	nrecv;

	nrecv = recv(this->__fd, buf, this->__buf_read.get_capacity(), MSG_NOSIGNAL);
	if (nrecv < 1)
		return false;
	else if (this->__timeout.get_ticks() < 500)
		return true;
	this->__timeout.start();
	if (this->__buf_read.get_size() + nrecv > this->__buf_read.get_capacity())
		return false;
	this->__buf_read.addstr(buf, nrecv);
	return true;
}

bool		User::add_buffer(const char* str, const unsigned int& size)
{
	unsigned int	add;

	add = this->__buf_write.addstr(str, size);
	return add == size;
}

void		User::rmv_buffer(unsigned int size)
{
	this->__buf_read.remove(size);
}

void		User::set_nation(e_land land)
{
	this->__land = land;
}

e_land		User::get_nation(void) const
{
	return this->__land;
}

bool		User::is_ready_to_play(void) const
{
	return this->__land != OTHER;
}

void	User::set_error(int error)
{
	this->__error = error;
}

int	User::get_error(void) const
{
	return this->__error;
}
