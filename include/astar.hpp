#ifndef __ASTAR__
#define __ASTAR__

#include <list>

template <typename Board, typename Node, typename Calcul_heuristic, typename Search_around, typename Is_equal>
class	Astar
{
	struct	My_node
	{
		Node*		node;
		My_node*	father;
		int		cost;
		int		total;
		My_node(): node(NULL), father(NULL), cost(0), total(0)
		{
		}
	};
	protected:
		std::list<My_node*>	open_list;
		std::list<My_node*>	close_list;
		My_node*		finish_node;
		Calcul_heuristic	calcul_heuristic;
		Search_around		search_around;
		Is_equal		is_equal;
	protected:
		My_node*		convert_node(Node* node)
		{
			My_node*	new_mynode;

			new_mynode = new (std::nothrow) My_node;
			if (node == NULL || new_mynode == NULL)
				return NULL;
			new_mynode->node = node;
			return new_mynode;
		}

		void			clear_list(std::list<My_node*>* list)
		{
			typename std::list<My_node*>::iterator	it;
			typename std::list<My_node*>::iterator	it_end;

			it = list->begin();
			it_end = list->end();
			while (it != it_end)
			{
				if (*it != NULL)
				{
					delete *it;
					it = list->erase(it);
				}
				else
					++it;
			}
		}

		std::list<My_node*>*	create_list_mynode(unsigned int size)
		{
			std::list<My_node*>*			list_mynode;
			My_node*				node;

			try
			{
				list_mynode = new std::list<My_node*>;
				for (unsigned int i = 0; i < size; ++i)
				{
					node = new My_node;
					list_mynode->push_back(node);
				}
			}
			catch (...)
			{
				this->clear_list(list_mynode);
				delete list_mynode;
				return NULL;
			}
			return list_mynode;
		}

		std::list<My_node*>*	convert_list_node(std::list<Node*>* node_list)
		{
			std::list<My_node*>*			list_mynode;
			typename std::list<My_node*>::iterator	it_mynode;
			typename std::list<Node*>::iterator	it;
			typename std::list<Node*>::iterator	it_end;

			list_mynode = this->create_list_mynode(node_list->size());
			if (list_mynode == NULL || node_list == NULL)
			{
				delete node_list;
				return NULL;
			}
			it = node_list->begin();
			it_end = node_list->end();
			it_mynode = list_mynode->begin();
			while (it != it_end)
			{
				(*it_mynode)->node = *it;
				++it;
				++it_mynode;
			}
			delete node_list;
			return list_mynode;
		}

		std::list<Node*>*	prepare_shortest_way(void)
		{
			typename std::list<My_node*>::reverse_iterator	rit;
			typename std::list<My_node*>::reverse_iterator	rit_end;
			std::list<Node*>*				node_list;
			My_node*					my_node;

			try
			{
				node_list = new std::list<Node*>;
				rit = this->close_list.rbegin();
				rit_end = this->close_list.rend();
				my_node = *rit;
				while (my_node != NULL)
				{
					node_list->push_front(my_node->node);
					my_node = my_node->father;
					++rit;
				}
			}
			catch (...)
			{
				this->clear_list(&this->close_list);
				return NULL;
			}
			this->clear_list(&this->close_list);
			return node_list;
		}

		bool			add_around_node(My_node* current_node, std::list<My_node*>* mynode_list)
		{
			typename std::list<My_node*>::iterator	it;
			typename std::list<My_node*>::iterator	it_end;

			it = mynode_list->begin();
			it_end = mynode_list->end();
			while (it != it_end)
			{
				if (this->node_already_exist(*it, &this->close_list))
				{
					++it;
					continue;
				}
				(*it)->total = calcul_heuristic((*it)->node, this->finish_node->node);
				if (this->node_already_exist(*it, &this->open_list) && (*it)->total < (*this->close_list.rbegin())->total)
					(*it)->father = current_node;
				else
					(*it)->father = *(this->close_list.rbegin());
				(*it)->total = calcul_heuristic((*it)->node, this->finish_node->node);
				if (!this->node_already_exist(*it, &this->open_list))
				{
					try
					{
						if (this->add_new_open_node(*it) == false)
							return false;
					}
					catch (...)
					{
						this->clear_list(mynode_list);
						delete mynode_list;
						return false;
					}
				}
				++it;
			}
			return true;
		}

		bool			add_new_open_node(My_node* my_node)
		{
			typename std::list<My_node*>::iterator	it;
			typename std::list<My_node*>::iterator	it_end;

			it = this->open_list.begin();
			it_end = this->open_list.end();
			while (it != it_end)
			{
				if (my_node->total < (*it)->total)
				{
					this->open_list.insert(it, my_node);
					return true;
				}
				++it;
			}
			this->open_list.insert(it, my_node);
			return true;
		}

		bool			node_already_exist(My_node* my_node, std::list<My_node*>* mynode_list)
		{
			typename std::list<My_node*>::iterator	it;
			typename std::list<My_node*>::iterator	it_end;

			it = mynode_list->begin();
			it_end = mynode_list->end();
			while (it != it_end)
			{
				if (this->is_equal(my_node->node, (*it)->node))
					return true;
				++it;
			}
			return false;
		}

		bool			move_node_open_to_closed(My_node* mynode)
		{
			try
			{
				this->open_list.remove(mynode);
				this->close_list.push_back(mynode);
			}
			catch (...)
			{
				return false;
			}
			return true;
		}

		bool			set_path(Node* start, Node* finish)
		{
			if (start == finish)
				return false;
			try
			{
				this->open_list.push_back(this->convert_node(start));
			}
			catch(...)
			{
				return false;
			}
			this->finish_node = this->convert_node(finish);
			return true;
		}

	public:
		Astar(void)
		{
		}

		~Astar(void)
		{
		}

		std::list<Node*>*	run(Node* start, Node* finish, Board* board)
		{
			My_node*	current_node;

			if (this->set_path(start, finish) == false)
				return NULL;
			try
			{
				current_node = *this->open_list.begin();
				while (this->open_list.size() > 0 && !this->is_equal(current_node->node, this->finish_node->node))
				{
					// Choose best node in open list
					current_node = *this->open_list.begin();
					// Move current to close_list
					if (this->move_node_open_to_closed(current_node) == false)
						return NULL;
					if (this->is_equal(current_node->node, this->finish_node->node))
					{
						this->clear_list(&this->open_list);
						return this->prepare_shortest_way();
					}
					// Check nodes around current node and add them to open list
					if (this->add_around_node(current_node, this->convert_list_node(this->search_around(current_node->node, board))) == false)
						return NULL;
				}
			}
			catch(...)
			{
				return NULL;
			}
			return NULL;
		}
};

#endif
