#ifndef __INTER_H__
#define __INTER_H__

#include "info.h"
#include "Lib2D.h"
class	Building;
class	Player;

struct t_products
{
	Lib2D::Container*	container;
	t_cost*			cost;
	Lib2D::Image*		cost_img[3];
};

class Inter : public Lib2D::Container
{
	Lib2D::Image*		__building;
	Lib2D::Label*		__name;
	Lib2D::Label*		__life[3];
	std::list<t_products>	__unit;

public:
	int			value;
	bool			launch_product;
				Inter();
	virtual			~Inter();
	bool			Init_Interface(Lib2D::Image** img, const char* name, Player* player, Building* building);
	bool			Head_Inter(Lib2D::Image* img, const char* name, Building* building);
	void			Delete_Interface(void);
	bool			Init_Production(Player* player);
	bool			Launch_product(Lib2D::Control* control, void* data);
	bool			Minus(Lib2D::Control* control, void* data);
	bool			Plus(Lib2D::Control* control, void* data);
};

#endif
