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

static int	check_task(t_tasker *handler)
{
	int	found;

	pthread_mutex_lock(&handler->self_lock);
	found = handler->_task;
	pthread_mutex_unlock(&handler->self_lock);
	return (found);
}

static void	clean_tasks(t_tasker *handler)
{
	pthread_mutex_lock(&handler->self_lock);
	handler->_task = 0;
	bzero(&handler->task, sizeof(t_task));
	pthread_mutex_unlock(&handler->self_lock);
}

void	set_tasker(t_tasker *handler, int id)
{
	handler->_task = 0;
	handler->id = id;
	handler->hastask = check_task;
	handler->clear = clean_tasks;
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
			handler->clear(handler);
		}
		else
			usleep(POOL_SLEEP);
	}
}

