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
#include "fcntl.h"

void		init_button(t_img *img, t_data *data, char *str)
{
	int		t[4];
	int		i1;
	int		i2;

	ft_memcpy(&t[0], &img->button[0], sizeof(int) * 4);
	draw_square(img, data, t);
	i1 = data->cellsize * 2;
	i2 = data->cellsize * 2;
	img->smile = mlx_xpm_file_to_image(img->mlx, str, &i1, &i2);
}

void		init_lines(t_img *img, t_data *data)
{
	int i;
	int j;
	int points[4];
	j = -1;
	while (++j < img->how_x)
	{
		i = -1;
		while (++i < img->how_y)
		{
			points[0] = data->img->shifty + i * data->cellsize;
			points[1] = data->img->shiftx + j * data->cellsize;
			points[2] = data->img->shifty + (i + 1) * data->cellsize;
			points[3] = data->img->shiftx + (j + 1) * data->cellsize;
			draw_square(img, data, points);
		}
	}
	init_button(img, data, "./xpm/Shout.xpm");
	// init_button(img, data, "./xpm/Love.xpm");
}

void		mine_one_random(int *x, int *y, t_data *data, unsigned int value)
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

void		mine_two_random(int *x, int *y, t_data *data, unsigned int value)
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

void		init_mines_in_field(t_data *data, unsigned int value, int fd)
{
	int minecount;
	int x;
	int y;

	minecount = -1;
	while (++minecount <= data->img->mines)
	{
		ft_printf("test[%d]!\n", minecount);
		read(fd, &value, sizeof(unsigned int));
		ft_printf("test[%d]:\n", minecount);
		// ft_printf("(%d) %u x:%d y:%d\n", minecount, value, x, y);
		if (minecount % 2 == 0)
		{
			mine_one_random(&x, &y, data, value);
			if (data->field[y][x] == 0)
				data->field[y][x] = -1;
			else
				--minecount;
		}
		else
		{
			mine_two_random(&x, &y, data, value);
			if (data->field[y][x] == 0)
				data->field[y][x] = -1;
			else
				--minecount;
		}
		// ft_printf("(%d) %u x:%d y:%d\n", minecount, value, x, y);
	}
}

void		increment_neighbor(int y, int x, t_data *data)
{
	if (y - 1 >= 0)
	{
		data->field[y - 1][x]++;
		if (x + 1 < data->img->how_x)
			data->field[y - 1][x + 1]++;
		if (x - 1 >= 0)
			data->field[y - 1][x - 1]++;
	}
	if (y + 1 < data->img->how_y)
	{
		data->field[y + 1][x]++;
		if (x + 1 < data->img->how_x)
			data->field[y + 1][x + 1]++;
		if (x - 1 >= 0)
			data->field[y + 1][x - 1]++;
	}
	if (x - 1 >= 0)
		data->field[y][x - 1]++;
	if (x + 1 < data->img->how_x)
		data->field[y][x + 1]++;
}

void		solve_distance(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->img->how_y)
	{
		j = -1;
		while (++j < data->img->how_x)
		{
			if (data->field[i][j] == -1)
			{
				ft_printf("i:%i j:%i check:%i\n", i, j);
				increment_neighbor(i, j, data);
			}
		}
	}
}

void		init_play_field(t_data *data)
{
	int i;
	int fd;

	i = -1;
	data->field = (char**)malloc(sizeof(char*) * data->img->how_y);
	while (++i < data->img->how_y)
	{
		data->field[i] = (char*)malloc(sizeof(char) * data->img->how_x);
		ft_bzero(data->field[i], sizeof(char) * data->img->how_x);
	}
	fd = open("/dev/urandom", O_RDONLY);
	init_mines_in_field(data, 0, fd);
	close(fd);
	solve_distance(&check, data);
	for (int i = 0; i < data->img->how_y; ++i)
	{
		for (int j = 0; j < data->img->how_y; ++j)
		{
			ft_printf("%d ", data->field[i][j]);
		}
		ft_printf("\n");
	}
}

void		init_img(t_data *data)
{
	t_img	*img;
	int		i;

	img = data->img;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, data->windowsizew, data->windowsizeh, "Mines42");
	img->img = mlx_new_image(img->mlx, data->windowsizew, data->windowsizeh);
	img->img_ptr = (int*)mlx_get_data_addr(img->img, &img->bpp, &img->sl, &img->endian);
	img->fillline = mlx_get_color_value(img->mlx, img->fillline);
	i = -1;
	while (++i < data->windowsizew * data->windowsizeh)
	{
		img->img_ptr[i] = 0xc0c0c0;
	}
}
