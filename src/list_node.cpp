#include "list_node.h"

id::list_node::list_node(void)
{


}

bool	id::list_node::insert(node* x)
{
	list<node*>::iterator	it(this->begin());
	list<node*>::iterator	it_end(this->end());

	while (it != it_end && x->score > (*it)->score)
		++it;
	try
	{
		list<node*>::insert(it, x);
	}
	catch (std::bad_alloc&)
	{
		return false;
	}
	return true;
}

bool	id::list_node::is_in_list(const Point& x)
{
	list<node*>::iterator	it(this->begin());
	list<node*>::iterator	it_end(this->end());

	while (it != it_end && (*it)->pos != x)
		++it;
	return it != it_end;
}

node*	id::list_node::get_node(const Point& x)
{
	list<node*>::iterator	it(this->begin());
	list<node*>::iterator	it_end(this->end());

	while (it != it_end && (*it)->pos != x)
		++it;
	if (it == it_end)
		return 0;
	return *it;
}

bool	id::list_node::sort(node* x)
{
	list<node*>::iterator	it(this->begin());
	list<node*>::iterator	it_end(this->end());

	while (it != it_end && *it != x)
		++it;
	this->erase(it);
	if (this->insert(x) == false)
		return false;
	return true;
}
