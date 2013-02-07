#ifndef __BUILDING_INTERFACE_H__
#define __BUILDING_INTERFACE_H__

#include <Lib2D.h>
#include "enums.h"
class Building;

class Building_Inter : public Lib2D::Container
{
public:
	Building_Inter();
	virtual~Building_Inter();
	bool	Create_Container(const char* wood, const char* gold);
	bool	Add_Img(e_ressource type, int y);
	bool	Add_Label(const char* wood, const char* gold);
	bool	set_building(e_type type);
private:
	Lib2D::Label*		__label_wood;
	Lib2D::Label*		__label_gold;
};

#endif
