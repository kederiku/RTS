#ifndef _INFO_IMG_H_
#define _INFO_IMG_H_

#include "point.h"
#include <Lib2D.h>

struct	info_img
{
	Point		sprite_pos;
	Point		sprite_size;
	Point		img_size;
	Lib2D::Image*	img_complete;

	bool	operator==(const info_img& right) const
	{
		return this->sprite_pos == right.sprite_pos && this->img_complete == right.img_complete;
	}
	info_img&	operator=(const info_img& right)
	{
		this->sprite_pos = right.sprite_pos;
		this->sprite_size = right.sprite_size;
		this->img_size = right.img_size;
		this->img_complete = right.img_complete;
		return *this;
	}
};

#endif
