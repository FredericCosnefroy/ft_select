/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 20:13:58 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/03/10 15:42:04 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE		64

# define EX_ERROR		-1
# define EX_SUCCESS		1
# define EX_CONTINUE	0
# define EX_EOF			0
# define FALSE			0
# define TRUE			1
# define EMPTY			""

typedef struct	s_mem
{
	char		*mem;
	int			fd;
}				t_mem;

int				get_next_line(int const fd, char **line);

#endif
