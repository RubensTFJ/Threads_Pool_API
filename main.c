#include "thread_pool.h"
#include <stdio.h>

#define V (void*)

int main(void)
{
	threads()->start();

	int id = threads()
		->deploy((t_task){V printf, "deploy 0\n"})
		->queue((t_task){V printf, "queue on 0\n"})->id;

	threads()
		->deploy((t_task){V printf, "new deploy 1\n"});

	threads()->wait();
	threads()->queue_to((t_task){V printf, "this print deployed on %i\n", V id}, id);
	printf("id deploy 0: %i\n", id);

	threads()->end();
}
