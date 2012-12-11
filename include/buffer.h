#ifndef __ID_BUF_H__
#define __ID_BUF_H__

#include <string.h>

class	Buffer
{
	char*	__buf;
	size_t	__size;
	size_t	__capa;
	size_t	__space;

	bool	realloc(unsigned int capa);
public:
	Buffer(void);
	~Buffer(void);

	size_t		get_size(void) const;
	size_t		get_capacity(void) const;
	size_t		get_space(void) const;
	bool		is_empty(void) const;
	const char*	get_data(void) const;
	bool		is_full(void) const;
	void		print(void) const;
	size_t		addstr(const char* str, size_t len);
	void		remove(size_t len);
	void		clear(void);
	void		swap(Buffer* tmp);
	bool		init(int capa);
};

#endif
