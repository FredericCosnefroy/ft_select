/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/27 19:36:20 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/04/04 14:29:19 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <limits.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <signal.h>

# define CELL_MARGIN	3
# define SELECTED		1
# define UNDERLINE		2
# define DIRECTORY		4
# define FILE			8

typedef struct		s_select
{
	char			*name;
	int				len;
	char			flags;
}					t_select;

typedef struct		s_env
{
	struct termios	tc;
	t_select		*select;
	int				fd;
	int				width;
	int				height;
	int				elem_num;
	int				col_num;
	int				max_strlen;
	int				elems_cols;
	int				print_index;
	int				seli;
}					t_env;

void				update_term(t_env *env);
void				restore_term(t_env *env);
int					init_fd(void);
void				init_term(t_env *env);

void				deselect_files(t_env *env);
void				deselect_directories(t_env *env);
int					select_files(t_env *env);
int					select_directories(t_env *env);
int					delete_selected(t_env *env);

void				print(t_env *env);
void				print_selected(t_env *env);

void				listen_signals(t_env *env);
t_env				*env_save(t_env *env);

void				ft_putnchar_fd(char c, const int n, const int fd);
int					get_col_size(t_select *select);
int					remove_elem(t_env *env, int index, int dir);
t_select			*init_select(int argc, char **argv);

#endif
