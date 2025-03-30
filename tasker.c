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

static void	tasker_destroy(t_tasker *this)
{
	t_tlist	*destroy;

	pthread_mutex_destroy(&this->self_lock);
	if (this->queue)
	{
		while (this->queue)
		{
			destroy = this->queue;
			this->queue = this->queue->next;
			free(destroy);
		}
	}
	*this = (t_tasker){0};
}

static int	tasker_check_task(t_tasker *this)
{
	int	found;

	pthread_mutex_lock(&this->self_lock);
	found = this->_task || this->queue;
	pthread_mutex_unlock(&this->self_lock);
	return (found);
}

static int	tasker_roll_tasks(t_tasker *this)
{
	t_tlist	*hold;

	pthread_mutex_lock(&this->self_lock);
	if (this->queue)
	{
		this->task = this->queue->content;
		hold = this->queue;
		this->queue = this->queue->next;
		free(hold);
	}
	else
	{
		this->_task = 0;
		this->task = (t_task){0};
	}
	pthread_mutex_unlock(&this->self_lock);
}

void	init_tasker(t_tasker *this, int id)
{
	this->_task = 0;
	this->id = id;
	this->hastask = tasker_check_task;
	this->roll_task = tasker_roll_tasks;
	this->destroy = tasker_destroy;
	pthread_mutex_init(&this->self_lock, NULL);
}

void	thread_hub(t_tasker *this)
{
	while (1)
	{
		if (this->hastask(this))
		{
			this->task.execute(this->task.arg1, this->task.arg2,
				this->task.arg3, this->task.arg4, this->task.arg5);
			this->roll_task(this);
		}
		else
			usleep(POOL_SLEEP);
	}
}

