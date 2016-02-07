/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 22:21:19 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/04/04 14:28:38 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	handle_default_actions(t_env *env, char buff[], int len, int *a)
{
	if (len == 3 && buff[0] == 27)
	{
		if (buff[2] == 'A')
			env->seli = env->seli ? env->seli - 1 : env->elem_num - 1;
		if (buff[2] == 'B')
			env->seli = (env->seli == env->elem_num - 1) ? 0 : env->seli + 1;
		if (buff[2] == 'C')
			env->seli += (env->seli + env->elems_cols > env->elem_num - 1) ?
				0 : env->elems_cols;
		if (buff[2] == 'D')
			env->seli -= (env->seli - env->elems_cols < 0) ?
				0 : env->elems_cols;
		if (buff[1] == 91 && buff[2] == 51)
			*a = remove_elem(env, env->seli, 1);
	}
	if (len == 1 && buff[0] == 127)
		*a = remove_elem(env, env->seli, 0);
	if (len == 1 && buff[0] == '\n')
		print_selected(env);
	if (len == 1 && *buff == 'f')
		*a = select_files(env);
	if (len == 1 && *buff == 'd')
		*a = select_directories(env);
	if (len == 1 && *buff == 'g')
		*a = delete_selected(env);
}

static void	handle_special_actions(t_env *env, char buff[], int len)
{
	if (len == 1 && buff[0] == 27)
	{
		restore_term(env);
		exit(0);
	}
	if (len == 1 && buff[0] == ' ')
	{
		env->select[env->seli].flags ^= SELECTED;
		env->seli = (env->seli == env->elem_num - 1) ? 0 : env->seli + 1;
	}
}

void		ft_select(t_env *env)
{
	char	buff[4];
	int		action;
	int		prev;
	int		len;

	ft_bzero(buff, 4);
	prev = 0;
	print(env);
	while ((len = (read(0, buff, 3))) > 0)
	{
		action = 0;
		prev = env->seli;
		handle_default_actions(env, buff, len, &action);
		handle_special_actions(env, buff, len);
		if (prev != env->seli || action || env->elem_num == 1)
		{
			env->select[prev].flags &= ~(UNDERLINE);
			env->select[env->seli].flags |= UNDERLINE;
			print(env);
		}
		ft_bzero(buff, 3);
	}
}

int			main(int argc, char **argv)
{
	t_env		env;

	if (argc == 1)
		return (0);
	env.fd = init_fd();
	env.select = init_select(argc, argv + 1);
	env.max_strlen = get_col_size(env.select) + CELL_MARGIN;
	env.print_index = 0;
	env.seli = 0;
	env.elem_num = argc - 1;
	init_term(&env);
	listen_signals(&env);
	ft_select(&env);
	return (0);
}
