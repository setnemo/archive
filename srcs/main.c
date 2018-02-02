/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:26:19 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/01 14:26:19 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_data(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || (str[i] == '-' &&  ft_isdigit(str[i + 1])))
		{
			if (str[i] == '-')
				i++;
			count++;
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
		if (str[i] == ',')
		{
			i++;
			while (ft_isdigit(str[i]) || HEXCHAR || HEXSYMB )
				i++;
		}
		i++;
	}
	return (count);
}

int	get_map(char **str, int point[2], int fd, t_buf *buf)
{
	int		ret;

	point[Y] = 0;
	while ((ret = get_next_line(fd, &buf->line)) > 0)
	{
		buf->lbuf = ft_strjoin(buf->line, " ");
		ft_strdel(&buf->line);
		if (point[Y] == 0)
		{
			*str = ft_strdup(buf->lbuf);
			point[X] = get_data(buf->lbuf);
		}
		else
		{
			if (point[X] != get_data(buf->lbuf))
				return (-1);
			buf->buf = ft_strjoin(*str, buf->lbuf);
			ft_strdel(str);
			*str = buf->buf;
		}
		free(buf->lbuf);
		point[Y]++;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	char	*map;
	t_mlx	data;
	t_buf	buf;
	int		fd;

	data.isize = (argc > 2 && ft_isdigit(argv[2][0])) ? ft_atoi(argv[2]) : 1000;
	data.colour = (argc > 3 && ft_isdigit(argv[3][0])) ? ft_atoi(argv[3]) : 0xFFFFFF;
	fd = (argc > 1) ? open(argv[1], O_RDONLY) : 0;
	if (fd == -1)
		return (0);
	if (get_map(&map, data.point, fd, &buf) < 0)
	{
		ft_printf("Error\n");
		exit(1);
	}
	ft_testintstr(data.point[X], "x");
	ft_testintstr(data.point[Y], "y");
	if (argc > 2)
		close(fd);
	fdf(map, &data);
	system("leaks -quiet fdf");
}
