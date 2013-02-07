#ifndef __ENV_HPP__
#define __ENV_HPP__

#include "server.h"
#include "client.h"
#include "control/display/object/image.h"
#include "ressources.h"
#include "ressource.h"
#include "state.h"

class	Env
{
	public:
		Server		server;
		Client		client;
		Ressource	ressource;
		State		state;
		inline static Env*	get_instance(void)
		{
			if (__instance == 0)
			{
				pthread_mutex_lock(&(__mutex));
				if (__instance == 0)
				{
					__instance = new (std::nothrow) Env;
					if (__instance == 0 || __instance->init() == false)
					{
						delete __instance;
						__instance = 0;
					}

				}
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
		bool			init(void)
		{
			if (this->ressource.init() == false)
				return false;
			return true;
		}
};

#endif
