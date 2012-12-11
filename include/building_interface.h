#ifndef __BUILDING_INTERFACE_H__
#define __BUILDING_INTERFACE_H__

#include <Lib2D.h>

class Building;

class Building_Inter : public Lib2D::Container
{
public:
				Building_Inter();
	virtual			~Building_Inter();
	bool			Create_Container(int x, int y, const char* wood, const char* stone, const char* gold);
	bool			Add_Img(Lib2D::Image& img);
	bool			Add_Label(const char* wood, const char* stone, const char* gold);
	Building*		building;

private:
	Lib2D::Label*		__label_wood;
	Lib2D::Label*		__label_stone;
	Lib2D::Label*		__label_gold;
};

#endif
