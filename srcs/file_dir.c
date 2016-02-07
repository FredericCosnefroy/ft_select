/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 18:58:55 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/04/04 14:28:00 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	deselect_files(t_env *env)
{
	int		i;

	i = 0;
	while (env->select[i].name)
	{
		if (env->select[i].flags & FILE)
			env->select[i].flags &= ~(SELECTED);
		i++;
	}
}

void	deselect_directories(t_env *env)
{
	int		i;

	i = 0;
	while (env->select[i].name)
	{
		if (env->select[i].flags & DIRECTORY)
			env->select[i].flags &= ~(SELECTED);
		i++;
	}
}

int		select_files(t_env *env)
{
	int		i;
	int		did_select;

	i = 0;
	did_select = 0;
	while (env->select[i].name)
	{
		if (env->select[i].flags & FILE)
		{
			if (!did_select && !(env->select[i].flags & SELECTED))
				did_select = 1;
			env->select[i].flags |= SELECTED;
		}
		i++;
	}
	if (!did_select)
		deselect_files(env);
	return (1);
}

int		select_directories(t_env *env)
{
	int		i;
	int		did_select;

	i = 0;
	did_select = 0;
	while (env->select[i].name)
	{
		if (env->select[i].flags & DIRECTORY)
		{
			if (!did_select && !(env->select[i].flags & SELECTED))
				did_select = 1;
			env->select[i].flags |= SELECTED;
		}
		i++;
	}
	if (!did_select)
		deselect_directories(env);
	return (1);
}

int		delete_selected(t_env *env)
{
	int		i;

	i = 0;
	while (env->select[i].name)
	{
		if (env->select[i].flags & SELECTED)
		{
			remove_elem(env, i, 1);
			i = -1;
		}
		i++;
	}
	return (1);
}
