#ifndef	_CASE_MAP_H_
#define _CASE_MAP_H_

struct	Case_map
{
	struct
	{
		char	x;
		char	y;
	}			pos_image;
	bool			collision;
	bool			init;
	Case_map(void): collision(0), init(false)
	{
	}
};


#endif
