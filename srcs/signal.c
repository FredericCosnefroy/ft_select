/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 19:00:21 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/04/04 14:28:49 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	sig_handler(int sig)
{
	if (sig == SIGWINCH)
	{
		update_term(env_save(NULL));
		print(env_save(NULL));
	}
	else if (sig == SIGTSTP)
	{
		restore_term(env_save(NULL));
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\032");
	}
	else if (sig == SIGCONT)
	{
		listen_signals(env_save(NULL));
		init_term(env_save(NULL));
		print(env_save(NULL));
	}
	else if (sig != SIGCHLD && sig != SIGURG && sig != SIGIO)
	{
		restore_term(env_save(NULL));
		exit(1);
	}
}

void		listen_signals(t_env *env)
{
	int		i;

	env_save(env);
	i = -1;
	while (++i < 32)
		signal(i, &sig_handler);
}

t_env		*env_save(t_env *env)
{
	static t_env *save;

	if (env)
		save = env;
	return (save);
}
