#ifndef _UI_H_
#define _UI_H_

#include <Lib2D.h>

Lib2D::Label*	create_label(const char* txt, int x, int y, int size_police, int color = 0xFFFFFFFF);
Lib2D::Label*	create_label(unsigned val, int x, int y, int size_police, int color = 0xFFFFFFFF);
Lib2D::Image*	create_bg(const char* txt, int width, int height);
Lib2D::Image*	create_img(Lib2D::Image* img, int x, int y, int width, int height);

#endif
