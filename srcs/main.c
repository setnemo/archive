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

void	ft_testintstr(int a, char *name)
{
	ft_printf("\x1b[31m TESTING: \x1b[0m%10.10s ::: %10.i\n", name, a);
}

int	get_data(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			count++;
			while (ft_isdigit(str[i]))
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

int	get_map(char **str, int point[2], int fd)
{
	char	*line;
	int		ret;

	point[Y] = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		line = ft_strjoin(line, " ");
		if (point[Y] == 0)
		{
			*str = ft_strdup(line);
			point[X] = get_data(line);
		}
		else
		{
			if (point[X] != get_data(line))
				return (-1);
			*str = ft_strjoin(*str, line);
		}
		free(line);
		point[Y]++;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	char	*map;
	t_mlx	*data;
	int		fd;

	data = (t_mlx*)malloc(sizeof(t_mlx));
	data->isize = (argc > 2 && ft_isdigit(argv[2][0])) ? ft_atoi(argv[2]) : 1000;
	data->colour = (argc > 3 && ft_isdigit(argv[3][0])) ? ft_atoi(argv[3]) : 0xFFFFFF;
	fd = (argc > 1) ? open(argv[1], O_RDONLY) : 0;
	if (fd == -1)
		return (0);
	get_map(&map, data->point, fd);
	ft_testintstr(data->point[X], "x");
	ft_testintstr(data->point[Y], "y");
	if (argc > 2)
		close(fd);
	fdf(map, data);
}
