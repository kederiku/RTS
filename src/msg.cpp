#include "response.h"
#include "ns_var.h"

void	msg::get_msg(char* ret) const
{
	switch (this->id_msg)
	{
		case GAME_FULL:
			ns_cmc::ns_var::f_str_cpy(ret, "la partie est deja pleine");
			break;
		case GAME_ALREADY_START:
			ns_cmc::ns_var::f_str_cpy(ret, "la partie a deja commencer");
			break;
		case PLAYER_LEFT:
			ns_cmc::ns_var::f_str_cpy(ret, "le jouer 0 est partie");
			ret[9] += this->data;
			break;
		case PLAYER_WIN:
			ns_cmc::ns_var::f_str_cpy(ret, "le jouer 0 a gagner la partie");
			ret[9] += this->data;
			break;
	}
}
