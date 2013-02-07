#ifndef _ASTAR_H_
#define _ASTAR_H_

#include "list_node.h"
#include "point.h"
#include "control.h"
#include "position.h"
class	Map;

class	astar
{
	unsigned		__width;
	unsigned		__height;
	id::list_node		__open;
	id::list_node		__close;
	Map*			__map;
	std::list<Point>*	__way;
	Lib2D::Control*		__unit;

	void		search_closet_point(const position& pos, Point& ret);
	void		get_closet_point(const Point& start, const Point& end, Point& ret);
	void		clear_list(void);
	bool		add_direction(const Point& pos, const Point& end, node* prev, const int& distance);
	bool		search_any_direction(const Point& pos, const Point& end, node* prev);
	node*		get_closest_node(void);
	bool		add_node(const Point& pos, const Point& end, node* prev, const int& distance);
	bool		find_path(const Point& begin, const Point& end);
public:
	astar(void);

	void	init(Map* map, std::list<Point>* way, Lib2D::Control* unit);
	bool	search_way(const Point& begin, const Point& end);
	bool	search_data(const Point& begin, bool (Map::*fct)(unsigned x, unsigned y) const);
	bool	get_way(bool reverse);
	bool	get_way(void (std::list<Point>::*fct)(const Point& add));
//	bool	get_way(bool first);
	bool	show_way(void) const;
};

#endif
