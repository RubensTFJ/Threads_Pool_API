#ifndef THREADER_H
# define THREADER_H

# include "thread_pool.h"
# include "tasker.h"

typedef struct s_fullthreader {
	t_threader	*(*deploy)(t_task);
	t_threader	*(*queue)(t_task);
	t_threader	*(*queue_to)(t_task, size_t);
	void		(*wait)(void);
	void		(*start)(void);
	void		(*end)(void);
	int			id;
	t_tasker	all[NOF_THREADS];
	int			on;
} t_fullthreader;

t_threader	*threader_give_task(t_task todo);
t_threader	*threader_queue_task(t_task todo);
t_threader	*threader_queue_task_to(t_task todo, size_t id);

#endif