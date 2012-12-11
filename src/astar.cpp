#include "astar.h"
#include "case_map.h"
#include <unistd.h>
#include <stdlib.h>

astar::astar(void)
{
}

void	astar::init(case_map** map, unsigned width, unsigned height)
{
	this->__map = map;
	this->__width = width;
	this->__height = height;
}

unsigned	astar::get_distance(const Point& begin, const Point& end)
{
	return 10 * (abs(end.x - begin.x) + abs(end.y - begin.y));
}

bool	astar::add_node(const Point& pos, const Point& end, node* prev, int distance)
{
	node*		way;

	try
	{
		way = new node();
		way->pos = pos;
		way->begin_distance = distance + 10 /*this->__map[pos.x][pos.y].cost*/;
		if (prev != 0)
			way->begin_distance += prev->begin_distance;
		way->end_distance = this->get_distance(pos, end);
		way->score = way->begin_distance + way->end_distance;
		way->prev = prev;
		this->__open.insert(way);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool	astar::is_case_valide(const Point& pos, case_map* obstacle)
{
	if (pos.x >= this->__width || pos.y >= this->__height)
		return false;
	if (obstacle != 0 /*&& this->__map[pos.x] + pos.y == obstacle*/)
		return false;
//	if (this->__map[pos.x][pos.y].cost > 50)
//		return false;
	return true;
}

bool	astar::add_direction(const Point& pos, const Point& end, node* prev, int distance)
{
	node*		tmp;
	unsigned int	begin_distance(0);

//	begin_distance = this->__map[pos.x][pos.y].cost + distance;
	if (prev != 0)
		begin_distance += prev->begin_distance;
	if (this->__close.is_in_list(pos) == true)
		return true;
	tmp = this->__open.get_node(pos);
	if (tmp != 0 && tmp->begin_distance <= begin_distance)
		return true;
	if (this->add_node(pos, end, prev, distance) == false)
		return false;
	return true;
}

bool	astar::check_diagonal(const Point& pos, bool left, bool right, case_map* obstacle)
{
	if (left && right && this->is_case_valide(pos, obstacle) == true)
		return true;
	return false;
}

bool	astar::search_any_direction(const Point& pos, const Point& end, node* prev, case_map* obstacle)
{
	Point		direction[4];
	unsigned	i(0);
	bool		diagonal[5];

	direction[0].x = 0;
	direction[0].y = -1;
	direction[1].x = 1;
	direction[1].y = 0;
	direction[2].x = 0;
	direction[2].y = 1;
	direction[3].x = -1;
	direction[3].y = 0;
	while (i < 4)
	{
		if (this->is_case_valide(pos + direction[i], obstacle) == true)
		{
			diagonal[i] = true;
			if (this->add_direction(pos + direction[i], end, prev, 10) == false)
				return false;
		}
		else
			diagonal[i] = false;
		++i;
	}
	diagonal[4] = diagonal[0];
	i = 0;
	direction[0].x = 1;
	direction[1].y = 1;
	direction[2].x = -1;
	direction[3].y = -1;
	while (i < 4)
	{
		if (diagonal[i] && diagonal[i + 1] && this->is_case_valide(pos + direction[i], obstacle) == true)
		{
			if (this->add_direction(pos + direction[i], end, prev, 14) == false)
				return false;
		}
		++i;
	}
	return true;
}

bool	astar::search_way(const Point& begin, const Point& end, case_map* obstacle)
{
	node*	tmp;

	this->clear_list();
	if (this->add_node(begin, end, 0, 0) == false)
		return false;
	while (this->__open.size() != 0)
	{
		tmp = this->__open.front();
		if (tmp->pos == end)
			break;
		this->__open.pop_front();
		this->__close.push_back(tmp);
		if (this->search_any_direction(tmp->pos, end, tmp, obstacle) == false)
			return false;
	}
	return true;
}

node*	astar::get_closest_node(void)
{
	node*			ret;
	id::list_node::iterator	it;

	ret = this->__close.front();
	it = this->__close.begin();
	while (it != this->__close.end())
	{
		if ((*it)->end_distance <= ret->end_distance)
			ret = *it;
		++it;
	}
	return ret;
}

bool	astar::get_way(std::list<Point>* ret, bool first)
{
	node*				tmp;
	std::list<Point>::iterator	it;
	Point				save;

	if (first == true)
		save = ret->front();
	if (this->__open.size() > 1)
		tmp = this->__open.front();
	else if (this->__close.size() != 0)
		tmp = this->get_closest_node();
	else
		return true;
	ret->clear();
	while (tmp->prev != 0)
	{
		ret->push_front(tmp->pos);
		tmp = tmp->prev;
	}
	if (first == true)
		ret->push_front(save);
	this->clear_list();
	return true;
}

bool	astar::show_way(void) const
{
	node*				tmp;
	std::list<Point>::iterator	it;
	std::list<Point>		way;

	if (this->__open.size() == 0)
		tmp = this->__close.front();
	else
		tmp = this->__open.front();
	while (tmp != 0)
	{
		way.push_front(tmp->pos);
		tmp = tmp->prev;
	}
	it = way.begin();
	while (it != way.end())
	{
		it->print();
		++it;
	}
	return true;
}

void	astar::clear_list(void)
{
	this->__open.clear();
	this->__close.clear();
}
