/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 18:50:37 by apakhomo          #+#    #+#             */
/*   Updated: 2017/12/26 18:50:38 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl	*while_gnl(t_gnl *gnl, int fd)
{
	while (gnl->next && gnl->fd != fd)
	{
		gnl = gnl->next;
		if (gnl->fd == fd)
			return (gnl);
	}
	if (gnl->fd != fd)
	{
		NOMEM((gnl->next = (t_gnl*)malloc(sizeof(t_gnl))));
		gnl->next->fd = fd;
		NOMEM((gnl->next->str = ft_strnew(0)));
		gnl->next->after = NULL;
		gnl->next->next = NULL;
		gnl = gnl->next;
	}
	return (gnl);
}

static int		gnl_core(t_gnl *gnl, char **line)
{
	char			*pointer;

	if (gnl->after)
		gnl->str = gnl->after;
	pointer = ft_strchr(gnl->str, 10);
	if (pointer)
	{
		ZERO(*pointer);
		ERR((*line = ft_strdup(gnl->str)));
		ERR((gnl->after = ft_strdup(pointer + 1)));
		free(gnl->str);
		return (1);
	}
	if (!(*gnl->str))
		return (0);
	else
		ERR((*line = ft_strdup(gnl->str)));
	gnl->after = gnl->str;
	ZERO(*gnl->after);
	free(gnl->str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*gnl;
	t_gnl			*buf;
	char			*temp;
	char			tmp[BUFF_SIZE + 1];
	int				i;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1 || read(fd, 0, 0) < 0)
		return (-1);
	if (!gnl)
	{
		ERR((gnl = (t_gnl*)malloc(sizeof(t_gnl))));
		gnl->fd = fd;
		ERR((gnl->str = ft_strnew(0)));
		gnl->after = NULL;
		gnl->next = NULL;
	}
	ERR((buf = while_gnl(gnl, fd)));
	while ((i = read(fd, tmp, BUFF_SIZE)))
	{
		ZERO(tmp[i]);
		ERR((temp = ft_strjoin(buf->str, tmp)));
		free(buf->str);
		buf->str = temp;
	}
	return (i < 0 ? -1 : gnl_core(buf, line));
}
