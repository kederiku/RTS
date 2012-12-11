#include <stdio.h>
#include "mutex.h"
#include <unistd.h>

Mutex::Mutex(pthread_mutex_t* mutex): __mutex(mutex)
{
	pthread_mutex_lock(this->__mutex);
}

Mutex::~Mutex(void)
{
	pthread_mutex_unlock(this->__mutex);
}
