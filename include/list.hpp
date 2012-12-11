#include <list>
#include <vector>

template <typename T>
void	clear_vector(std::vector<T>& vector)
{
	typename std::vector<T>::iterator	it(vector.begin());

	while (it != vector.end())
	{
		delete *it;
		it = vector.erase(it);
	}
}

template <typename T>
void	clear_list(std::list<T>& list)
{
	typename std::list<T>::iterator	it(list.begin());

	while (it != list.end())
	{
		delete *it;
		it = list.erase(it);
	}
}

namespace	id
{
	template <typename T>
	class	list: public std::list<T>
	{
	public:
		~list(void)
		{
			this->clear();
		}
		void	clear(void)
		{
			typename std::list<T>::iterator	it;

			it = this->begin();
			while (it != this->end())
			{
				delete *it;
				it = this->erase(it);
			}
		}
	};
}
