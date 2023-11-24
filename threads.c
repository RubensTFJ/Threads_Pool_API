/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:03:41 by rteles-f          #+#    #+#             */
/*   Updated: 2023/11/09 21:20:56 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

static void	give_task(t_task todo)
{
	static int	i;
	t_tasker	*handler;

	handler = ((t_fullthreader *)threads())->all;
	while (todo.execute)
	{
		pthread_mutex_lock(&handler[i].self_lock);
		if (!handler[i]._task)
		{
			handler[i].task = todo;
			handler[i]._task = 1;
			todo.execute = NULL;
		}
		pthread_mutex_unlock(&handler[i].self_lock);
		i = (i + 1) * (i < (NOF_THREADS - 1));
	}
}

static void	wait_threads(void)
{
	int			i;
	t_tasker	*handlers;

	handlers = ((t_fullthreader *)threads())->all;
	i = 0;
	while (i < NOF_THREADS)
	{
		while (handlers[i].hastask(&handlers[i]))
			usleep(10);
		i++;
	}
}

static void	end_threads(void)
{
	int			i;
	t_tasker	*handlers;

	if (!((t_fullthreader *)threads())->on)
		return ;
	else
		((t_fullthreader *)threads())->on = 0;
	i = 0;
	while (i < NOF_THREADS)
	{
		threads()->deploy((t_task){pthread_exit, NULL});
		i++;
	}
	handlers = ((t_fullthreader *)threads())->all;
	i = 0;
	while (i < NOF_THREADS)
	{
		pthread_join(handlers[i].thread, NULL);
		pthread_mutex_destroy(&handlers[i].self_lock);
		i++;
	}
	bzero(handlers, sizeof(t_tasker) * NOF_THREADS);
}

static void	init_threads(void)
{
	int			i;
	t_tasker	*handlers;

	if (((t_fullthreader *)threads())->on)
		return ;
	else
		((t_fullthreader *)threads())->on = 1;
	handlers = ((t_fullthreader *)threads())->all;
	i = 0;
	while (i < NOF_THREADS)
	{
		set_tasker(&handlers[i], i);
		pthread_create(&handlers[i].thread, NULL,
			(void *)thread_hub, &handlers[i]);
		i++;
	}
}

inline t_threader	*threads(void)
{
	static t_fullthreader	manager = {
		give_task,
		wait_threads,
		init_threads,
		end_threads,
	};

	return ((t_threader *)&manager);
}
