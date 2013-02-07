#ifndef	_NETWORK_H_
#define _NETWORK_H_

#include "response.h"
#include "buffer.h"
#include <pthread.h>
#include <iostream>
struct	addrinfo;

class	Network
{
	pthread_t*	__threads;
	bool		__init;
protected:
	addrinfo*	_res;
	int		_sockfd;

	Network(void);
	virtual ~Network(void);

	bool		init(const char* port, const char* ip);
	bool		create_thread(void);
	void		init_timeout(timeval& timeout);
	void		set_init(bool init);
public:
	bool		is_run(void) const;
	void		quit(void);
	virtual bool	run(void) = 0;
	virtual bool	clear(void);
	template <typename T>
	T*		get_msg(const Buffer& buf) const
	{
		T	check;
		T*	ret;

		if (buf.is_empty() == true)
			return 0;
		ret = (T*)buf.get_data();
		if (ret->type != check.type || ret->size > buf.get_size())
			return 0;
		return ret;
	}
};


#endif
