/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <fcosnefr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 12:43:40 by fcosnefr          #+#    #+#             */
/*   Updated: 2015/03/10 15:39:58 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include "get_next_line.h"

static t_mem	*get_mem_fd(const int fd, t_list **lst_ptr)
{
	t_list	*lst;
	t_mem	mem;

	lst = *lst_ptr;
	while (lst)
	{
		if (((t_mem *)lst->content)->fd == fd)
			return (lst->content);
		lst = lst->next;
	}
	mem.fd = fd;
	mem.mem = EMPTY;
	if (!(lst = ft_lstnew(&mem, sizeof(t_mem))))
		return (NULL);
	ft_lstadd(lst_ptr, lst);
	return ((*lst_ptr)->content);
}

static int		add_line(char **line, char **mem, char *str)
{
	int		len;

	if ((len = ft_strchri(str, '\n')) >= 0)
	{
		if (!(*line = ft_strfjoin(*line, ft_strsub(str, 0, len), TRUE, TRUE)))
			return (EX_ERROR);
		*mem = &str[len] + 1;
		return (EX_SUCCESS);
	}
	if (!(*line = ft_strfjoin(*line, str, TRUE, FALSE)))
		return (EX_ERROR);
	return (EX_CONTINUE);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*lst = NULL;
	t_mem			*mem;
	char			*buff;
	int				ret;

	if (!(buff = ft_strnew(BUFF_SIZE)) || !line || fd < 0 ||
		!(mem = get_mem_fd(fd, &lst)) ||
		!(*line = ft_strnew(1)))
		return (free(buff), EX_ERROR);
	if (*(mem->mem) != '\0')
		if (add_line(line, &(mem->mem), mem->mem) == EX_SUCCESS)
			return (free(buff), EX_SUCCESS);
	mem->mem = EMPTY;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (add_line(line, &(mem->mem), buff) == EX_SUCCESS)
			return (EX_SUCCESS);
		buff = ft_memset(buff, '\0', BUFF_SIZE);
	}
	if (ret < 0)
		return (free(buff), EX_ERROR);
	if (!ret && !ft_strcmp(buff, EMPTY) && !ft_strcmp(*line, EMPTY))
		return (free(buff), EX_EOF);
	return (free(buff), EX_SUCCESS);
}
