#include "astar.h"
#include "map.h"
#include "info_pos.h"
#include <unistd.h>
#include <stdlib.h>

astar::astar(void): __way(0)
{
}

void	astar::init(Map* map, std::list<Point>* way, Lib2D::Control* unit)
{
	this->__map = map;
	this->__way = way;
	this->__unit = unit;
}

bool	astar::add_node(const Point& pos, const Point& end, node* prev, const int& distance)
{
	node*		way;

	try
	{
		way = new node();
		way->pos = pos;
		way->begin_distance = distance;
		way->end_distance = this->__map->get_distance(pos, end);
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

bool	astar::add_direction(const Point& pos, const Point& end, node* prev, const int& distance)
{
	node*		tmp;
	unsigned int	begin_distance(distance);

	if (prev != 0)
		begin_distance += prev->begin_distance;
	if (this->__close.is_in_list(pos) == true)
		return true;
	tmp = this->__open.get_node(pos);
	if (tmp != 0)
	{
		if (begin_distance < tmp->begin_distance)
		{
			tmp->begin_distance = begin_distance;
			tmp->score = begin_distance + tmp->end_distance;
			tmp->prev = prev;
			return this->__open.sort(tmp);
		}
		return true;
	}
	if (this->add_node(pos, end, prev, begin_distance) == false)
		return false;
	return true;
}

bool	astar::search_any_direction(const Point& pos, const Point& end, node* prev)
{
	info_pos	neighbor[8];
	unsigned	size(0);
	unsigned	i(0);
	Point*		next;

	if (this->__map->get_neighbor(pos, neighbor, size, this->__unit) == false)
		return false;
	while (i < size)
	{
		next = neighbor + i;
		if (this->add_direction(*next, end, prev, ((info_pos*)next)->distance) == false)
			return false;
		++i;
	}
	return true;
}

void	astar::search_closet_point(const position& pos, Point& ret)
{
	while (this->__map->is_case_valid(ret, Point(ret.x * 32, ret.y * 32), this->__unit) == false)
	{
		ret.y += pos.y;
		ret.x += pos.x;
	}
}

void	astar::get_closet_point(const Point& start, const Point& end, Point& ret)
{
	position	pos;

	if (start.x > end.x)
		++pos.x;
	else if (start.x < end.x)
		--pos.x;
	if (start.y > end.y)
		++pos.y;
	else if (start.y < end.y)
		--pos.y;
	this->search_closet_point(pos, ret);
}

bool	astar::find_path(const Point& begin, const Point& end)
{
	node*	tmp;

	if (this->add_node(begin, end, 0, 0) == false)
		return false;
	while (this->__open.empty() == false)
	{
		tmp = this->__open.front();
		if (tmp->pos == end)
			break;
		this->__open.pop_front();
		this->__close.push_back(tmp);
		if (this->search_any_direction(tmp->pos, end, tmp) == false)
			return false;
	}
	return true;
}

bool	astar::search_way(const Point& begin, const Point& end)
{
	if (begin == end)
		return true;
	this->clear_list();
	if (this->__map->is_case_valid(end, Point(end.x * 32, end.y * 32), this->__unit) == false)
	{
		if (this->find_path(end, begin) == false)
			return false;
		return this->get_way(&std::list<Point>::push_back);
	}
	else
	{
		if (this->find_path(begin, end) == false)
			return false;
		return this->get_way(&std::list<Point>::push_front);
	}
}

node*	astar::get_closest_node(void)
{
	node*			ret(this->__close.front());
	id::list_node::iterator	it(this->__close.begin());
	id::list_node::iterator	it_end(this->__close.end());

	while (it != it_end)
	{
		if ((*it)->end_distance < ret->end_distance)
			ret = *it;
		++it;
	}
	return ret;
}

bool	astar::get_way(void (std::list<Point>::*push)(const Point& add))
{
	node*				tmp;
	std::list<Point>::iterator	it;
	Point				save;

	if (this->__open.size() > 1)
		tmp = this->__open.front();
	else if (this->__close.size() > 1)
		tmp = this->get_closest_node();
	else
		return true;
	this->__way->clear();
	try
	{
		while (tmp->prev != 0)
		{
			(this->__way->*push)(tmp->pos);
			tmp = tmp->prev;
		}
	}
	catch (std::exception&)
	{
		return false;
	}
	this->clear_list();
	return true;
}

void	astar::clear_list(void)
{
	this->__open.clear();
	this->__close.clear();
}
