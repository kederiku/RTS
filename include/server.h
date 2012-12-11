#ifndef _SERVER_H_
#define _SERVER_H_

#include "network.h"
#include <list>
#include <sys/types.h>
class	User;
class	info_struct;

class	Server: public Network
{
	std::list<User*>	__client;
	unsigned		__nb_player_max;

	bool	add_client(int& fd_max);
	void	init_fd(fd_set* fdsr, fd_set* fdsw);
	void	check_fd(fd_set* fdsr, fd_set* fdsw, int& fd_max);
	void	send_message(const info_struct* msg);
	bool	update_statut_game(void);
	bool	parser_buffer(User* user);
	bool	choose_nation(User* user);
	bool	close_client(User* user) const;
	void	send_msg(User* user, msg_type type, int data = 0);
public:
	Server(void);
	virtual ~Server(void);

	bool		run(void);
	bool		init(const char* port, const char* ip, unsigned nb_player = 4);
	virtual bool	clear(void);
};

#endif
