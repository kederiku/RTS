#include "waiting_room.h"
#include "response.h"

Waiting_room::Waiting_room(void)
{

}

Waiting_room::~Waiting_room(void)
{

}

bool	Waiting_room::derived_treat_event(Lib2D::Event* event)
{
	(void) event;
//	std::cout << "waiing room event" << std::endl;
	return true;
}
