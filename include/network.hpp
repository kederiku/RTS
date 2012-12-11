#include "server.h"
#include "client.h"
#include "game.h"

template <typename T>
void*	fct_run(void* data)
{
	T*	t((T*)data);

	t->run();
	return 0;
}
