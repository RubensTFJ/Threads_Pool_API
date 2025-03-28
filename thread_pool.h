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

typedef struct s_task
{
	void		(*execute)();
	void		*arg1;
	void		*arg2;
	void		*arg3;
	void		*arg4;
	void		*arg5;
} t_task;

typedef struct s_threader
{
	int			(*deploy)(t_task);
	void		(*queue)(t_task);
	void		(*queue_to)(t_task);
	void		(*wait)(void);
	void		(*start)(void);
	void		(*end)(void);
} t_threader;

t_threader			*threads(void);

#endif
