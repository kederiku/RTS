
#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

#include "list.hpp"
#include "node.h"
#include "point.h"

namespace	id
{
	class	list_node: public id::list<node*>
	{
	public:
		void	insert(node* x);
		bool	is_in_list(const Point& x);
		node*	get_node(const Point& x);
	};
}

#endif
