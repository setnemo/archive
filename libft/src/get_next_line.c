/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:16:45 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/27 18:58:46 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*searchlist(t_list **list, int fd)
{
	t_list *tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if ((int)(tmp->content_size) == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		tmp = ft_lstnew(NULL, 0);
		tmp->content_size = fd;
		ft_lstadd(&(*list), tmp);
	}
	return (tmp);
}

static int		find_line(t_list *file, char **line)
{
	void	*ptr_buf;
	int		len;
	int		ost;

	len = 0;
	if (ft_strlen(file->content) == 0)
		return (0);
	ptr_buf = file->content;
	ptr_buf = ft_strchr(file->content, '\n');
	if (ptr_buf == NULL)
	{
		*line = ft_strdup(file->content);
		ft_bzero(file->content, ft_strlen(file->content));
		return (1);
	}
	len = ptr_buf - file->content;
	*line = ft_strsub(file->content, 0, len);
	ptr_buf = file->content;
	ost = ft_strlen(&(file->content)[len]);
	file->content = ft_strsub(ptr_buf, len + 1, ost);
	free(ptr_buf);
	return (1);
}

static int		sub_gnl(t_list **file, char *tmp)
{
	char	*buf;

	buf = NULL;
	if ((*file)->content == NULL)
	{
		buf = ft_strsub(tmp, 0, ft_strlen(tmp));
		(*file)->content = buf;
	}
	else
	{
		buf = (*file)->content;
		(*file)->content = ft_strjoin((*file)->content, tmp);
		free(buf);
	}
	if (ft_strchr(tmp, '\n') != NULL)
	{
		ft_bzero(tmp, BUFF_SIZE);
		return (1);
	}
	ft_bzero(tmp, BUFF_SIZE);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*file;
	t_list			*tmp_f;
	char			*tmp;
	int				i;

	i = 0;
	if (fd < 0 || line == NULL)
		return (-1);
	if (!(tmp = ft_strnew(BUFF_SIZE)))
		return (0);
	tmp_f = searchlist(&file, fd);
	while ((i = read(fd, tmp, BUFF_SIZE)) > 0)
		if (sub_gnl(&tmp_f, tmp) == 1)
			break ;
	ft_strdel(&tmp);
	if (i < 0)
		return (-1);
	if (tmp_f->content == NULL || ft_strlen(tmp_f->content) == 0)
		return (0);
	if (find_line(tmp_f, &(*line)) == 0 && i == 0)
		return (0);
	return (1);
}
