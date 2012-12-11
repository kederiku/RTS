#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <network.h>
#include <sys/types.h>
#include <iostream>
#define SIZE_BUFFER_WRITE 400
#define SIZE_BUFFER_READ  400

class	Client: public Network
{
	Buffer	__buf_write;
	Buffer	__buf_read;

	bool		write(void);
	bool		read(void);
	bool		alloc_buffer(void);
	void		init_fd(fd_set* fdsr, fd_set* fdsw);
	bool		send_to_server(const info_struct* msg);
public:
	Client(void);
	virtual ~Client(void);

	bool		add_buffer(const char* str, unsigned int size);
	bool		init(const char* port, const char* ip);
	bool		run(void);
	virtual bool	clear(void);
	template <typename T>
	T*		get_msg() const
	{
		return Network::get_msg<T>(this->__buf_read);
	}
	void	remove_buffer_read(unsigned int size);
	bool	send_nation(const e_land land);
	bool	game_start(void);
	bool	update_data(void);
};

#endif
