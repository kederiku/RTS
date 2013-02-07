#include "response.h"
#include "ns_var.h"

void	msg::get_msg(char* ret) const
{
	*ret = 0;
	switch (this->id_msg)
	{
		case LOGIN :
			break;
		case LOGOUT :
			ns_cmc::ns_var::f_str_cpy(ret, "le joueur 0 est parti");
			ret[10] += this->data;
			break;
		case WELCOME :
			break;
		case GAME_FULL :
			ns_cmc::ns_var::f_str_cpy(ret, "la partie est deja pleine");
			break;
		case GAME_ALREADY_START :
			ns_cmc::ns_var::f_str_cpy(ret, "la partie a deja commence");
			break;
		case PLAYER_WIN :
			ns_cmc::ns_var::f_str_cpy(ret, "le joueur 0 a gagne la partie");
			ret[10] += this->data;
			break;
	}
}
