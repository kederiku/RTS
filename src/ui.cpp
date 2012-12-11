#include "ressources.h"
#include <Lib2D.h>

Lib2D::Label*	create_label(const char* txt, int x, int y, int size_police)
{
	Lib2D::Label*	label(new (std::nothrow)Lib2D::Label);

	if (label == 0)
		return 0;
	label->move(x, y);
	if (label->init(txt, FONT, size_police) == false)
	{
		delete label;
		return 0;
	}
	return label;
}


Lib2D::Image*	create_bg(const char* txt, int width, int height)
{
	Lib2D::Image*	bg(new (std::nothrow)Lib2D::Image);

	if (bg == 0)
		return 0;
	bg->resize(width, height);
	bg->move(0, 0);
	if (bg->load_bmp(txt) == false)
	{
		delete bg;
		return 0;
	}
	return bg;
}


Lib2D::Image*	create_img(Lib2D::Image* img, int x, int y, int width, int height)
{
	Lib2D::Image*	ret;

	ret = img->get_image_part(x, y , width, height);
	if (ret == 0)
		return 0;
	ret->set_transparence(0, 255, 0);
	ret->resize(width, height);
	return ret;
}
