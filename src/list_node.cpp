#include "list_node.h"

void	id::list_node::insert(node* x)
{
	list<node*>::iterator	it;

	it = this->begin();
	while (it != this->end() && x->score > (*it)->score)
		++it;
	list<node*>::insert(it, x);
}

bool	id::list_node::is_in_list(const Point& x)
{
	list<node*>::iterator	it;

	it = this->begin();
	while (it != this->end() && (*it)->pos != x)
		++it;
	return it != this->end();
}

node*	id::list_node::get_node(const Point& x)
{
	list<node*>::iterator	it;

	it = this->begin();
	while (it != this->end() && (*it)->pos != x)
		++it;
	if (it == this->end())
		return 0;
	return *it;
}
