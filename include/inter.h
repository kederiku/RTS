#ifndef __INTER_H__
#define __INTER_H__

#include "info.h"
#include "Lib2D.h"
#include "enums.h"
class	Building;
class	Player;
class	Unit;
class	Ressources;

struct t_products
{
	Lib2D::Container*	container;
	t_cost*			cost;
};

class Inter : public Lib2D::Container
{
	Lib2D::Image*		__building;
	Lib2D::Label*		__name;
	t_products		__unit;
	Building*		__id_building;

public:
				Inter();
	virtual			~Inter();
	bool			Init_Interface(Lib2D::Image** img, const char* name, Player* player, Building* building, Unit* unit);
	bool			Head_Inter_Building(Lib2D::Image* img, const char* name, Building* building);
	bool			Head_Inter_Unit(Lib2D::Image* img, const char* name, Unit* unit);
	bool			Head_Inter_Ressource(Lib2D::Image* img, const char* name, Ressources* ressource);
	bool			Head_Inter(Lib2D::Image* img, char* hp, const char* name);
	void			Delete_Interface(void);
	bool			Init_Production(Player* player);
	bool			Launch_product(Lib2D::Control* control, void* data);
	bool			Minus(Lib2D::Control* control, void* data);
	bool			Plus(Lib2D::Control* control, void* data);
	bool			Add_Label(Unit* unit);
	bool			Add_Icon(e_ressource image, int y);
	
};

#endif
