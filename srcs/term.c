/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 19:00:49 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/04/04 14:49:35 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	update_term(t_env *env)
{
	struct winsize	win;

	ioctl(2, TIOCGWINSZ, &win);
	env->width = win.ws_col;
	env->height = win.ws_row;
	env->elems_cols = env->height - 1;
	env->col_num = (env->width - 20) / env->max_strlen;
}

void	restore_term(t_env *env)
{
	ft_putstr_fd(tgetstr("cl", NULL), env->fd);
	ft_putstr_fd(tgetstr("te", NULL), env->fd);
	ft_putstr_fd(tgetstr("ve", NULL), env->fd);
	if (tcsetattr(0, TCSADRAIN, &(env->tc)) < 0)
		ft_putstr_fd("Error : Can't restore termios attr.\n", 2);
}

int		init_fd(void)
{
	int		fd;

	fd = open(ttyname(0), O_WRONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error : ft_select needs a terminal.\n", 2);
		exit(-1);
	}
	return (fd);
}

void	init_term(t_env *env)
{
	char			*term;
	struct termios	tc;

	if ((term = getenv("TERM")) == NULL)
		term = "";
	if (tgetent(NULL, term) <= 0)
	{
		ft_putstr_fd("Error : Invalid TERM.\n", 2);
		exit(1);
	}
	if (tcgetattr(0, &tc) < 0)
		exit(1);
	ft_memcpy(&(env->tc), &tc, sizeof(struct termios));
	tc.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
	tc.c_cc[VMIN] = 1;
	tc.c_cc[VTIME] = 5;
	if (tcsetattr(0, TCSADRAIN, &tc))
	{
		ft_putstr_fd("Error : Can't set termios attributes\n", 2);
		exit(1);
	}
	ft_putstr_fd(tgetstr("ti", NULL), env->fd);
	ft_putstr_fd(tgetstr("vi", NULL), env->fd);
	update_term(env);
}
