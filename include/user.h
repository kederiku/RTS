#ifndef _USER_H_
#define _USER_H_

#include "point.h"
#include "buffer.h"
#include "control/timer.h"
#include "enums.h"
#include "buffer_size.h"

class	User
{
	Buffer			__buf_write;
	Buffer			__buf_read;
	Lib2D::Timer		__timeout;
	int			__fd;
	e_land			__land;
	int			__error;
	int			__tick;
public:
	User(void);
	~User(void);

	bool		init(const int& sckfd);
	int		get_fd(void) const;
	const Buffer&	get_buf_write(void) const;
	const Buffer&	get_buf_read(void) const;
	bool		read(void);
	bool		write(void);
	bool		add_buffer(const char* str, const unsigned int& size);
	void		rmv_buffer(unsigned int size);
	void		set_nation(e_land land);
	e_land		get_nation(void) const;
	bool		is_ready_to_play(void) const;
	void		set_error(int error);
	int		get_error(void) const;
	int		get_tick(void) const;
	void		set_tick(int tick);

};
#endif
