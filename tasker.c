/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:55:18 by rteles-f          #+#    #+#             */
/*   Updated: 2023/10/15 22:55:18 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"
#include "tasker.h"

static int	tasker_check_task(t_tasker *handler)
{
	int	found;

	pthread_mutex_lock(&handler->self_lock);
	found = handler->_task || handler->queue;
	pthread_mutex_unlock(&handler->self_lock);
	return (found);
}

static void	tasker_roll_tasks(t_tasker *handler)
{
	t_tlist	*hold;

	pthread_mutex_lock(&handler->self_lock);
	if (handler->queue)
	{
		handler->task = handler->queue->content;
		hold = handler->queue;
		handler->queue = handler->queue->next;
		free(hold);
	}
	else
	{
		handler->_task = 0;
		bzero(&handler->task, sizeof(t_task));
	}
	pthread_mutex_unlock(&handler->self_lock);
}

void	init_tasker(t_tasker *handler, int id)
{
	handler->_task = 0;
	handler->id = id;
	handler->hastask = tasker_check_task;
	handler->roll_task = tasker_roll_tasks;
	pthread_mutex_init(&handler->self_lock, NULL);
}

void	thread_hub(t_tasker *handler)
{
	while (1)
	{
		if (handler->hastask(handler))
		{
			handler->task.execute(handler->task.arg1, handler->task.arg2,
				handler->task.arg3, handler->task.arg4, handler->task.arg5);
			handler->roll_task(handler);
		}
		else
			usleep(POOL_SLEEP);
	}
}

