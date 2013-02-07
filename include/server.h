#ifndef _SERVER_H_
#define _SERVER_H_

#include "network.h"
#include <list>
#include <sys/types.h>
#include "user.h"
struct	info_struct;

class	Server: public Network
{
	std::list<User*>	__client;
	unsigned		__nb_player_max;
	bool			__game_start;
	int			__tick;

	bool	add_client(int& fd_max);
	void	init_fd(fd_set* fdsr, fd_set* fdsw);
	void	check_fd(fd_set* fdsr, fd_set* fdsw, int& fd_max);

	bool	parser_buffer(User* user);
	void	add_buffer_client(const info_struct* msg, int id = -1);
	bool	close_client(User* user) const;

	bool	update_statut_game(void);
	bool	choose_nation(User* user);
	void	send_msg(User* user, msg_type type, int data = 0);
	bool	send_info_player(int id_player);

	bool	check_tick(int tick) const;
	void	set_tick(int tick);
	template <typename T>
	bool	send_to_all_player(User* user)
	{
		T*	data(Network::get_msg<T>(user->get_buf_read()));

		if (data == 0)
			return false;
		this->add_buffer_client(data);
		return true;
	}
public:
	Server(void);
	virtual ~Server(void);

	bool		run(void);
	bool		init(const char* port, const char* ip, unsigned nb_player = 4);
	virtual bool	clear(void);
};

#endif
