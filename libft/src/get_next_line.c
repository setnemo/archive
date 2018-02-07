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

#include "libft.h"

static t_gnl	*while_gnl(int fd)
{
	static t_gnl	*gnl;

	if (!gnl)
	{
		NOMEM((gnl = (t_gnl*)malloc(sizeof(t_gnl))));
		gnl->fd = fd;
		gnl->after = NULL;
		gnl->next = NULL;
	}
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
		gnl->next->after = NULL;
		gnl->next->next = NULL;
		gnl = gnl->next;
	}
	NOMEM((gnl->str = ft_strnew(0)));
	return (gnl);
}

static int		gnl_core(t_gnl *gnl, char **line)
{
	char	*p;

	if (gnl->after)
	{
		gnl->str = ft_strjoin(gnl->after, gnl->str);
		free(gnl->after);
	}
	p = ft_strchr(gnl->str, 10);
	if (p)
	{
		*p = 0;
		*line = ft_strdup(gnl->str);
		if (ft_strlen(gnl->str) + gnl->str > p)
			gnl->after = ft_strdup(p + 1);
		free(gnl->str);
		return (1);
	}
	if (!(*gnl->str))
		return 0;
	*line = ft_strdup(gnl->str);
	free(gnl->str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	t_gnl			*buf;
	char			*temp;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1 || read(fd, 0, 0) < 0)
		return (-1);
	ERR((buf = while_gnl(fd)));
	buf->tmp = ft_strnew(BUFF_SIZE);
	while ((buf->br = read(fd, buf->tmp, BUFF_SIZE)))
	{
		temp = ft_strjoin(buf->str, buf->tmp);
		free(buf->str);
		buf->str = temp;
		ft_strclr(buf->tmp);
		BRK((ft_strchr(buf->str, 10)));
	}
	free(buf->tmp);
	return (gnl_core(buf, line));
}
