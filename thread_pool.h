/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:56:55 by rteles-f          #+#    #+#             */
/*   Updated: 2023/10/15 22:56:55 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>

# define NOF_THREADS 4
# define POOL_SLEEP 20

typedef pthread_mutex_t		t_mutex;
typedef struct s_tasker		t_tasker;
typedef struct s_task		t_task;
typedef struct s_threader	t_threader;

struct s_task {
	void		(*execute)();
	void		*arg1;
	void		*arg2;
	void		*arg3;
	void		*arg4;
	void		*arg5;
};

struct s_tasker {
	int			id;
	int			_task;
	int			(*hastask)(t_tasker *);
	void		(*clear)(t_tasker *);
	pthread_t	thread;
	t_task		task;
	t_mutex		self_lock;
};

struct s_threader {
	void		(*deploy)(t_task);
	void		(*wait)(void);
	void		(*start)(void);
	void		(*end)(void);
};

typedef struct s_fullthreader {
	void		(*deploy)(t_task);
	void		(*wait)(void);
	void		(*start)(void);
	void		(*end)(void);
	t_tasker	all[NOF_THREADS];
	int			on;
} t_fullthreader;

t_threader			*threads(void);
void				thread_hub(t_tasker *handler);
void				set_tasker(t_tasker *handler, int id);

#endif
