#ifndef __MUTEX_HEADER__
#define __MUTEX_HEADER__

#include <pthread.h>

class	Mutex
{
private:
	pthread_mutex_t*	__mutex;
public:
	Mutex(pthread_mutex_t* mutex);
	~Mutex(void);
};

#endif
