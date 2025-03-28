#ifndef THREADER_H
# define THREADER_H

# include "thread_pool.h"
# include "tasker.h"

typedef struct s_fullthreader {
	int			(*deploy)(t_task);
	void		(*queue)(t_task);
	void		(*queue_to)(t_task);
	void		(*wait)(void);
	void		(*start)(void);
	void		(*end)(void);
	t_tasker	all[NOF_THREADS];
	int			last_deploy;
	int			on;
} t_fullthreader;

int		threader_give_task(t_task todo);
void	threader_queue_task(t_task todo);
void	threader_queue_task_to(t_task todo, size_t id);

#endif