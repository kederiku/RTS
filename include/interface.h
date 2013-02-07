#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#define  NB_BUILDING 6
#include <Lib2D.h>
#include "building_interface.h"

class	Building_Inter;
class	Game;
class	Player;

class	Interface
{
	Lib2D::Image	__image_source;
	Building*	__building[NB_BUILDING];
	Building_Inter*	__build[NB_BUILDING];
	Lib2D::Label*	__label_wood;
	Lib2D::Label*	__label_gold;
	Lib2D::Label*	__label_popu;

	bool	make_image(Game* game, int x, int y, int w, int h, int x2, int y2);
	bool	init_building(Game* game, e_type*);
public:
	Interface(void);
	~Interface(void);

	bool	init(Game* game, e_land);
	bool	init_nation_interface(Game*, e_land);
	void	set_visible_building(bool visible);
	bool	check_ressource(Player* player);

};

#endif
