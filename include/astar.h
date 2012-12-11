#ifndef _ASTAR_H_
#define _ASTAR_H_

#include "list_node.h"
#include "point.h"
struct	case_map;

class	astar
{
	unsigned		__width;
	unsigned		__height;
	id::list_node		__open;
	id::list_node		__close;
	case_map** 		__map;

	bool		check_diagonal(const Point& pos, bool left, bool right, case_map* obstacle);
	int		get_dir(Point* ret, const Point& pos, case_map* obstacle);
	bool		is_case_valide(const Point& pos, case_map* obstacle);
	void		clear_list(void);
	unsigned	get_distance(const Point& begin, const Point& end);
	bool		add_direction(const Point& pos, const Point& end, node* prev, int distance);
	bool		search_any_direction(const Point& pos, const Point& end, node* prev, case_map* obstacle);
	node*		get_closest_node(void);
	bool		add_node(const Point& pos, const Point& end, node* prev, int distance);
public:
	astar(void);

	void		init(case_map** map, unsigned width, unsigned height);
	bool		search_way(const Point& begin, const Point& end, case_map* obstacle);
	bool		get_way(std::list<Point>* ret, bool first);
	bool		show_way(void) const;
};

#endif
