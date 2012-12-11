#ifndef __BUILDING_INFO_H__
#define __BUILDING_INFO_H__

#include <Lib2D.h>

class	Building_Info : public Lib2D::Container
{
public:
	Building_Info();
	~Building_Info();

	bool	Create_Container(int x, int y);
}

#endif
