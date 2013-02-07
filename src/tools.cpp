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

void	id::itoa(unsigned int value, char* buf)
{
	int	i(1);

	while ((value / i) >= 10)
		i *= 10;
	while (i > 0)
	{
		*buf = (value / i) % 10 + '0';
		++buf;
		i /= 10;
	}
	*buf = 0;
}
