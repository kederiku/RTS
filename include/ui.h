#ifndef _UI_H_
#define _UI_H_

Lib2D::Label*	create_label(const char* txt, int x, int y, int size_police);
Lib2D::Image*	create_bg(const char* txt, int width, int height);
Lib2D::Image*	create_img(Lib2D::Image* img, int x, int y, int width, int height);

#endif
