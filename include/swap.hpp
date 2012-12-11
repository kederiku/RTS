#ifndef	_SWAP_HPP_
#define _SWAP_HPP_

template <class T>
void	id_swap(T* x, T* y)
{
	T	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

#endif
