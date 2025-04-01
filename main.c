#include "thread_pool.h"
#include <stdio.h>
#include <stdint.h>

#define V (void*)
#define SV (void *)(intptr_t)

void	wrap_printf(void *a, void *b, void *c, void *d, void *e)
{
	(void)c, (void)d, (void)e;
	printf(a, *(int**)&b);
}

int main(void)
{
	threads()->start();

	int id = threads()
		->deploy((t_task){printf, .arg1 = "deploy 0\n"})
		->queue((t_task){.execute = printf, "queue on 0\n"})->id;

	threads()->deploy((t_task){.execute = printf, "new deploy 1\n"});

	threads()->wait();
	threads()->queue_to((t_task){.execute = wrap_printf, "this print deployed on %i\n", SV id}, id);

	threads()->end();
}
