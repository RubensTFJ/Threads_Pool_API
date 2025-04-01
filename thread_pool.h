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

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

# define NOF_THREADS 4
# define POOL_SLEEP 20

typedef struct s_threader t_threader;

typedef struct s_task
{
	// void		(*execute)();
	void		*execute;
	void		*arg1;
	void		*arg2;
	void		*arg3;
	void		*arg4;
	void		*arg5;
} t_task;

struct s_threader
{
	t_threader	*(*deploy)(t_task);
	t_threader	*(*queue)(t_task);
	t_threader	*(*queue_to)(t_task, size_t);
	void		(*wait)(void);
	void		(*start)(void);
	void		(*end)(void);
	int			id;
};

t_threader			*threads(void);

#endif
