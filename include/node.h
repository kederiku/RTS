#ifndef _NODE_H_
#define _NODE_H_

#include "point.h"

struct	node
{
	Point		pos;
	unsigned	begin_distance;
	unsigned	end_distance;
	unsigned	score;
	node*		prev;

	node(void);
	~node(void);
};

#endif
