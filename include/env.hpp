#ifndef __ENV_HPP___
#define __ENV_HPP__

#include "server.h"
#include "client.h"

class	Env
{
	public:
		Server	server;
		Client	client;
		inline static Env*	get_instance(void)
		{
			if (__instance == 0)
			{
				pthread_mutex_lock(&(__mutex));
				if (__instance == 0)
					__instance = new (std::nothrow) Env;
				pthread_mutex_unlock(&(__mutex));
			}
			return __instance;
		};
		static void		kill(void)
		{
			delete __instance;
			__instance = 0;
		};
	protected:
		Env(void)
		{
			pthread_mutex_init(&(this->__mutex), 0);
		}
		virtual ~Env(void)
		{
			pthread_mutex_destroy(&(this->__mutex));
		}
	private:
		static	Env*		__instance;
		static	pthread_mutex_t	__mutex;
};



#endif
