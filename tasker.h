/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasker.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:21:32 by rteles-f          #+#    #+#             */
/*   Updated: 2025/04/01 13:23:42 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TASKER_H
# define TASKER_H

# include <pthread.h>
# include "thread_pool.h"

typedef pthread_mutex_t		t_mutex;
typedef struct s_tasker		t_tasker;
typedef struct s_threader	t_threader;

typedef struct s_tlist
{
	t_task			content;
	struct s_tlist	*next;
}	t_tlist;

struct s_tasker
{
	int			id;
	int			_task;
	int			(*hastask)(t_tasker *);
	int			(*roll_task)(t_tasker *);
	void		(*destroy)(t_tasker *);
	pthread_t	thread;
	t_task		task;
	t_tlist		*queue;
	t_mutex		self_lock;
};

void	thread_hub(t_tasker *handler);
void	init_tasker(t_tasker *handler, int id);

#endif