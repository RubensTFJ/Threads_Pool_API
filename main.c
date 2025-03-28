#include "thread_pool.h"
#include <stdio.h>

int main(void)
{
	threads()->start();

	threads()->deploy((t_task){printf, "testing\n"});
	threads()->wait();

	threads()->end();
}