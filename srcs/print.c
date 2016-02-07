/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 19:12:53 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/04/04 14:28:12 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void		print_colored(t_env *env, int index)
{
	if (env->select[index].flags & FILE)
		ft_putstr_fd("1;36m", env->fd);
	else if (env->select[index].flags & DIRECTORY)
		ft_putstr_fd("1;34m", env->fd);
	else
		ft_putstr_fd("1;37m", env->fd);
	write(env->fd, env->select[index].name, env->select[index].len);
}

static void		print_select(t_env *env, int index, int x, int y)
{
	ft_putstr_fd("\33[0m", env->fd);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), x, y), env->fd);
	if (!x && index >= env->elems_cols)
		ft_putstr_fd(STR_FORMAT("", STR_BOLD, STR_GREEN, " <<   "), env->fd);
	else
		write(env->fd, "      ", 6);
	if (index == env->seli)
	{
		ft_putstr_fd(STR_FORMAT("", STR_BOLD, STR_YELLOW, "> "), env->fd);
		ft_putstr_fd("\33[4;", env->fd);
	}
	else
	{
		write(env->fd, "  ", 3);
		ft_putstr_fd("\33[", env->fd);
	}
	if (env->select[index].flags & SELECTED)
		ft_putstr_fd("7;", env->fd);
	print_colored(env, index);
	if (index == env->seli)
		ft_putstr_fd(STR_FORMAT("", STR_BOLD, STR_YELLOW, " <"), env->fd);
	ft_putnchar_fd(' ', env->max_strlen - env->select[index].len - CELL_MARGIN,
			env->fd);
	if (index + env->elems_cols < env->elem_num)
		ft_putstr_fd(STR_FORMAT("", STR_BOLD, STR_GREEN, "   >>"), env->fd);
}

static int		print_init(t_env *env)
{
	int		selected_col;

	ft_putstr_fd("\33[0m", env->fd);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), env->fd);
	ft_putstr_fd(tgetstr("cd", NULL), env->fd);
	if (!env->elems_cols || env->width < env->max_strlen + 21)
	{
		ft_putstr_fd("win too small", env->fd);
		return (-1);
	}
	selected_col = env->seli / env->elems_cols;
	while (selected_col > (env->col_num - 1) + env->print_index)
		env->print_index++;
	while (selected_col < env->print_index)
		env->print_index--;
	return (env->print_index * env->elems_cols);
}

void			print(t_env *env)
{
	int		i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if ((i = print_init(env)) < 0)
		return ;
	while (env->select[i].name &&
			i < ((env->col_num) + env->print_index) * env->elems_cols)
	{
		if (i != env->print_index * env->elems_cols && !(i % env->elems_cols))
		{
			x += env->max_strlen + CELL_MARGIN;
			y = 0;
		}
		else if (i != env->print_index * env->elems_cols)
			y++;
		print_select(env, i, x, y);
		i++;
	}
}

void			print_selected(t_env *env)
{
	int		i;
	int		printed;

	i = 0;
	printed = 0;
	ft_putstr_fd("\33[0m", env->fd);
	restore_term(env);
	while (env->select[i].name)
	{
		if (env->select[i].flags & SELECTED)
		{
			if (printed)
				ft_putchar(' ');
			ft_putstr(env->select[i].name);
			printed = 1;
		}
		i++;
	}
	if (printed)
		ft_putchar('\n');
	exit(0);
}
