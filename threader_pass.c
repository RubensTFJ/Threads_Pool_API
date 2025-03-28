#include "thread_pool.h"
#include "tasker.h"
#include "threader.h"

void	threader_queue_task_to(t_task todo, size_t id)
{
	t_tasker		*handler;
	t_tlist			*tail;
	t_tlist			*new;

	if (id >= NOF_THREADS)
		return ;
	handler = &(((t_fullthreader *)threads())->all[id]);
	new = calloc(1, sizeof(t_tlist));
	new->content = todo;
	pthread_mutex_lock(&handler->self_lock);
	if (!handler->queue)
		handler->queue = new;
	else
	{
		tail = handler->queue;
		while (tail->next)
			tail = tail->next;
		tail->next = new;
	}
	pthread_mutex_unlock(&handler->self_lock);
}

void	threader_queue_task(t_task todo)
{
	threader_queue_task_to(todo, ((t_fullthreader*)threads())->last_deploy);
}

int	threader_give_task(t_task todo)
{
	static int	id;
	t_tasker	*handler;

	handler = ((t_fullthreader *)threads())->all;
	while (todo.execute)
	{
		pthread_mutex_lock(&handler[id].self_lock);
		if (!handler[id]._task)
		{
			handler[id].task = todo;
			handler[id]._task = 1;
			todo.execute = NULL;
			((t_fullthreader *)threads())->last_deploy = id;
		}
		pthread_mutex_unlock(&handler[id].self_lock);
		++id;
		if (id >= NOF_THREADS)
			id = 0;
	}
	return (((t_fullthreader *)threads())->last_deploy);
}
