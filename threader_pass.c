/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader_pass.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:25:16 by rteles-f          #+#    #+#             */
/*   Updated: 2025/04/01 13:27:25 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"
#include "tasker.h"
#include "threader.h"
#include <stdio.h>

t_threader	*threader_queue_task_to(t_task todo, size_t id)
{
	t_tasker		*handler;
	t_tlist			**tail;
	t_tlist			*new_node;

	if (id >= NOF_THREADS)
		return (threads());
	handler = &(((t_fullthreader *)threads())->all[id]);
	new_node = calloc(1, sizeof(t_tlist));
	new_node->content = todo;
	pthread_mutex_lock(&handler->self_lock);
	tail = &(handler->queue);
	while (*tail)
		tail = &((*tail)->next);
	*tail = new_node;
	pthread_mutex_unlock(&handler->self_lock);
	return (threads());
}

t_threader	*threader_queue_task(t_task todo)
{
	threader_queue_task_to(todo, ((t_fullthreader *)threads())->id);
	return (threads());
}

// Use queue_task_to to pass the task instead.
// Then change all access from the task variable
//to look into the queue instead.
t_threader	*threader_give_task(t_task todo)
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
			((t_fullthreader *)threads())->id = id;
		}
		pthread_mutex_unlock(&handler[id].self_lock);
		++id;
		if (id >= NOF_THREADS)
			id = 0;
	}
	return (threads());
}
