/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 19:01:38 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/04/04 14:29:01 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void			ft_putnchar_fd(char c, const int n, const int fd)
{
	int		i;
	char	pad[n];

	i = -1;
	while (++i < n)
		pad[i] = c;
	write(fd, pad, n);
}

int				get_col_size(t_select *select)
{
	int		i;
	int		max;

	i = 0;
	max = 0;
	while (select[i].name)
	{
		if (select[i].len > max)
			max = select[i].len;
		i++;
	}
	return (max);
}

static void		set_seli(t_env *env, int dir)
{
	if (!dir)
		env->seli -= (env->elem_num && env->seli >= env->elem_num &&
			env->seli - 1 >= 0) ? 1 : 0;
	else
		env->seli -= (env->seli - 1 >= 0) ? 1 : 0;
}

int				remove_elem(t_env *env, int index, int dir)
{
	t_select	*select;
	int			i;
	int			j;

	i = 0;
	j = 0;
	env->elem_num--;
	if (env->elem_num > 0)
	{
		select = (t_select *)malloc(sizeof(t_select) * (env->elem_num + 1));
		while (env->select[j].name)
		{
			select[i] = env->select[j];
			if (j != index)
				i++;
			j++;
		}
		select[i] = (t_select){0, 0, 0};
		free(env->select);
		env->select = select;
		set_seli(env, dir);
		return (1);
	}
	restore_term(env);
	exit(0);
}

t_select		*init_select(int argc, char **argv)
{
	struct stat	sstat;
	t_select	*select;
	int			i;

	i = 0;
	select = (t_select *)malloc(sizeof(t_select) * argc);
	while (argv[i])
	{
		select[i].flags = 0;
		select[i].name = argv[i];
		select[i].len = ft_strlen(argv[i]);
		select[i].flags |= !i ? UNDERLINE : 0;
		if (stat(select[i].name, &sstat) != -1)
		{
			if (S_ISDIR(sstat.st_mode))
				select[i].flags |= DIRECTORY;
			else
				select[i].flags |= FILE;
		}
		i++;
	}
	select[i] = (t_select){0, 0, 0};
	return (select);
}
