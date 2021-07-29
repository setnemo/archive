/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

static void	mine_one_random(int *x, int *y, t_data *data, unsigned int value)
{
	*x = value / data->img->how_y;
	while (*x > data->img->how_x)
		*x /= (data->img->how_x / 2);
	*y = value % data->img->how_y;
	if (*x >= data->img->how_x)
		*x = data->img->how_x - 1;
	if (*y >= data->img->how_y)
		*y = data->img->how_y - 1;

}

static void	mine_two_random(int *x, int *y, t_data *data, unsigned int value)
{
	*y = value / data->img->how_y;
	while (*y > data->img->how_y)
		*y /= (data->img->how_y / 2);
	*x = value % data->img->how_x;
	if (*x >= data->img->how_x)
		*x = data->img->how_x - 1;
	if (*y >= data->img->how_y)
		*y = data->img->how_y - 1;
}

static void	init_mines_in_field(t_data *data, unsigned int value, int fd, int first[])
{
	int minecount;
	int x;
	int y;

	minecount = -1;
	while (++minecount < data->img->mines)
	{
		read(fd, &value, sizeof(unsigned int));
		// ft_printf("(%d) %u x:%d y:%d\n", minecount, value, x, y);
		if (minecount % 2 == 0)
		{
			mine_one_random(&x, &y, data, value);
			if (data->field[y][x] == 0 && first[0] != y && first[1] != x)
				data->field[y][x] = -1;
			else
				--minecount;
		}
		else
		{
			mine_two_random(&x, &y, data, value);
			if (data->field[y][x] == 0 && first[0] != y && first[1] != x)
				data->field[y][x] = -1;
			else
				--minecount;
		}
		// ft_printf("(%d) %u x:%d y:%d\n", minecount, value, x, y);
	}
}


void		init_play_field(t_data *data, int x, int y)
{
	int i;
	int fd;
	int first[2];

	i = -1;
	first[0] = y;
	first[1] = x;
	data->field = (char**)malloc(sizeof(char*) * data->img->how_y);
	data->show = (char**)malloc(sizeof(char*) * data->img->how_y);
	// ft_printf("==========>%p\n===========>%p\n", data->field, data->show);
	while (++i < data->img->how_y)
	{
		data->field[i] = (char*)malloc(sizeof(char) * data->img->how_x);
		ft_bzero(data->field[i], sizeof(char) * data->img->how_x);
		data->show[i] = (char*)malloc(sizeof(char) * data->img->how_x);
		ft_bzero(data->show[i], sizeof(char) * data->img->how_x);
		// ft_printf("=%i=========>%p\n===========>%p\n", i, data->field[i], data->show[i]);
	}
	fd = open("/dev/urandom", O_RDONLY);
	init_mines_in_field(data, 0, fd, first);
	close(fd);
	// for (int i = 0; i < data->img->how_y; ++i)
	// {
	// 	for (int j = 0; j < data->img->how_x; ++j)
	// 	{
	// 		ft_printf("%d ", data->field[i][j]);
	// 	}
	// 	ft_printf("\n");
	// }
	solve_distance(data);
	// for (int i = 0; i < data->img->how_y; ++i)
	// {
	// 	for (int j = 0; j < data->img->how_x; ++j)
	// 	{
	// 		ft_printf("%d ", data->show[i][j]);
	// 	}
	// 	ft_printf("\n");
	// }
}