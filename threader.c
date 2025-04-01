/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:03:41 by rteles-f          #+#    #+#             */
/*   Updated: 2025/04/01 13:24:31 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"
#include "tasker.h"
#include "threader.h"

static void	threader_wait(void)
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

// threads()->deploy((t_task){pthread_exit, NULL});
static void	threader_end(void)
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
		threader_queue_task_to((t_task){.execute = pthread_exit, NULL}, i);
		i++;
	}
	handlers = ((t_fullthreader *)threads())->all;
	i = 0;
	while (i < NOF_THREADS)
	{
		pthread_join(handlers[i].thread, NULL);
		handlers[i].destroy(&(handlers[i]));
		i++;
	}
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
		init_tasker(&handlers[i], i);
		pthread_create(&handlers[i].thread, NULL,
			(void *)thread_hub, &handlers[i]);
		i++;
	}
}

inline t_threader	*threads(void)
{
	static t_fullthreader	manager = {
		threader_give_task,
		threader_queue_task,
		threader_queue_task_to,
		threader_wait,
		init_threads,
		threader_end,
		.id = 0
	};

	return ((t_threader *)&manager);
}
