#ifndef _WAITING_ROOM_H_
#define _WAITING_ROOM_H_

#include "control/display/multi/popup_m.h"

class	Waiting_room: public Lib2D::Popup_m
{
public:
	Waiting_room(void);
	~Waiting_room(void);
	virtual bool	derived_treat_event(Lib2D::Event* event);
};


#endif
