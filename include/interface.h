#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#define  NB_BUILDING 7
#include <Lib2D.h>

class	Building_Inter;

class	Interface
{
public:
			Interface();

	Building_Inter*	building[NB_BUILDING];

	bool		Init(void);
	bool		Init_Img(void);
	bool		Make_image(Lib2D::Container* container, int x, int y, int w, int h, int x2, int y2);
	bool		Init_Building(void);
	bool		Create_Building(Lib2D::Control* a, void* b);
	bool		delete_building(int i);

	Lib2D::Container*	Get_Img(void);
	Lib2D::Container*	Get_Gold_Img(void);
	Lib2D::Container*	Get_Wood_Img(void);
	Lib2D::Container*	Get_Food_Img(void);
	Lib2D::Container*	Get_Stone_Img(void);
	Lib2D::Container*	Get_Population_Img(void);
private:

	Lib2D::Image*		__image_source;
	Lib2D::Container*	__img_interface;
	Lib2D::Container*	__img_gold;
	Lib2D::Container*	__img_wood;
	Lib2D::Container*	__img_food;
	Lib2D::Container*	__img_stone;
	Lib2D::Container*	__img_population;
};

#endif
