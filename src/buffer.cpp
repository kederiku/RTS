#include "buffer.h"
#include "tools.h"
#include "swap.hpp"
#include <iostream>
#include <string.h>

Buffer::Buffer(void): __buf(0), __size(0), __capa(0), __space(0)
{
}

Buffer::~Buffer(void)
{
	delete [] this->__buf;
}

bool	Buffer::init(int capa)
{
	if (this->__buf != 0)
		return this->realloc(capa);
	this->__buf = new (std::nothrow) char [capa];
	if (this->__buf == 0)
		return false;
	this->__size = 0;
	this->__capa = capa;
	this->__space = capa;
	return true;
}

size_t	Buffer::get_size(void) const
{
	return this->__size;
}

size_t	Buffer::get_capacity(void) const
{
	return this->__capa;
}

size_t	Buffer::get_space(void) const
{
	return this->__space;
}

bool	Buffer::is_empty(void) const
{
	if (this->__size == 0)
		return true;
	return false;
}

const char*	Buffer::get_data(void) const
{
	return this->__buf;
}

bool	Buffer::is_full(void) const
{
	if (this->__space == 0)
		return true;
	return false;
}

void	Buffer::print(void) const
{
	size_t	i;

	i = this->__size;
	while (i < this->__size)
	{
		++i;
	}
}

size_t	Buffer::addstr(const char* str, size_t len)
{
	size_t	i(0);

	while (i < len && this->__space > 0)
	{
		this->__buf[this->__size] = str[i];
		++i;
		++this->__size;
		--this->__space;
	}
	return i;
}

void	Buffer::remove(size_t len)
{
	size_t	i;

	i = 0;
	while (i + len < this->__size)
	{
		this->__buf[i] = this->__buf[i + len];
		++i;
	}
	this->__size -= len;
	this->__space += len;
}

bool	Buffer::realloc(unsigned int capa)
{
	char*	tmp;

	if (this->__capa <= capa)
		return true;
	tmp = new (std::nothrow) char [capa];
	if (tmp == 0)
		return false;
	this->__space = this->__capa - this->__size;
	this->__capa = this->__capa;
	id::strncpy(tmp, this->__buf, this->__size);
	delete [] this->__buf;
	this->__buf = tmp;
	return true;
}

void	Buffer::clear(void)
{
	this->__size = 0;
	this->__space = this->__capa;
}

void	Buffer::swap(Buffer* tmp)
{
	id_swap(&this->__buf, &tmp->__buf);
	id_swap(&this->__size, &tmp->__size);
	id_swap(&this->__capa, &tmp->__capa);
	id_swap(&this->__space, &tmp->__space);
}
