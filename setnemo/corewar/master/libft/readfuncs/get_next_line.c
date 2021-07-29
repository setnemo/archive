/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:31:39 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/16 15:31:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static int		cut_and_return(t_line *temp_line, char **line, size_t idx)
{
	char	*new_line;
	char	*temp;
	int		last;

	last = (temp_line->r_bytes == 0 &&
			temp_line->line_size == idx + 1) ? 1 : 0;
	new_line = ft_strsub(temp_line->line, 0, idx + last);
	*line = new_line;
	temp_line->line_size -= (idx + 1);
	temp_line->line_buf_size = (((temp_line->line_size) /
								BUFF_SIZE) + 1) * BUFF_SIZE;
	temp = ft_strnew(temp_line->line_buf_size);
	ft_strncpy(temp, (temp_line->line + idx + 1), temp_line->line_size);
	free(temp_line->line);
	temp_line->line = temp;
	return (1);
}

static int		read_to_temp_line(int fd, t_line *temp_line)
{
	char			*temp;

	if (temp_line->line_size + BUFF_SIZE > temp_line->line_buf_size)
	{
		temp_line->line_buf_size += BUFF_SIZE;
		temp = ft_strnew(temp_line->line_buf_size);
		ft_strncpy(temp, temp_line->line, temp_line->line_size);
		free(temp_line->line);
		temp_line->line = temp;
	}
	if (temp_line->r_bytes > 0)
	{
		temp_line->r_bytes = read(fd, (temp_line->line +
									temp_line->line_size), BUFF_SIZE);
		temp_line->line_size += temp_line->r_bytes;
	}
	return (1);
}

void			init_temp_line(t_line **temp_line)
{
	t_line *t;

	t = (t_line*)malloc(sizeof(t_line));
	t->line = ft_strnew(BUFF_SIZE);
	t->r_bytes = 1;
	t->line_buf_size = BUFF_SIZE;
	t->line_size = 0;
	*temp_line = t;
}

int				get_next_line(const int fd, char **line)
{
	static t_line	*temp_line;
	size_t			idx;

	if (temp_line == NULL)
		init_temp_line(&temp_line);
	while (1)
	{
		idx = 0;
		if (temp_line->line_size == 0 && temp_line->r_bytes == 0)
			return (0);
		while (idx < temp_line->line_size)
		{
			if (temp_line->line[idx] == '\n' ||
				(temp_line->r_bytes == 0 && temp_line->line_size == idx + 1))
				return (cut_and_return(temp_line, line, idx));
			idx++;
		}
		read_to_temp_line(fd, temp_line);
	}
}
