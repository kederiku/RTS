#include "tools.h"

void	id::memset(void* ptr, int value, unsigned num)
{
	unsigned	i(0);
	char*		c((char*)ptr);

	while (i < num)
	{
		c[i] = value;
		++i;
	}
}

char*	id::strncpy(char* str, const char* src, int size)
{
	int	i(0);

	while (i < size)
	{
		str[i] = src[i];
		++i;
	}
	return str;
}
