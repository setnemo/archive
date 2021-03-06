/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

// void		draw_stop(t_data *data, int flag)
// {

// 	;
// }

void		draw_square(t_img *img, t_data *data, int points[])
{
	// ft_printf("points[%d][%d][%d][%d]\n", points[0],  points[1],  points[2],  points[3]);
	int temp;

	temp = points[1];
	while (points[0] != points[2] - 1)
	{
		points[1] = temp;
		while (points[1] != points[3] - 1)
		{
			img->img_ptr[points[0] * img->sl / 4 + points[1] - 1] = data->img->fillline;
			points[1]++;
		}
		points[0]++;
	}
}

void		init_xpm(t_img *img, t_data *data, char *str)
{
	int		i1;
	int		i2;

	i1 = data->cellsize;
	i2 = data->cellsize;
	// ft_printf("size[%d:%d]", i1, i2);
	img->xpm = mlx_xpm_file_to_image(img->mlx, str, &i1, &i2);
}

void		draw_xpm(t_data *data, int flag, int x, int y);

void		bfs_zero_show(t_data *data, int flag, int x, int y)
{
	if (y - 1 >= 0)
	{
		if (data->show[y - 1][x] != -2)
			draw_xpm(data, data->field[y - 1][x], x, y - 1);
		if (x + 1 < data->img->how_x && data->show[y - 1][x + 1] != -2)
			draw_xpm(data, data->field[y - 1][x + 1], x + 1, y - 1);
		if (x - 1 >= 0 && data->show[y - 1][x - 1] != -2)
			draw_xpm(data, data->field[y - 1][x - 1], x - 1, y - 1);
	}
	if (y + 1 < data->img->how_y)
	{
		if (data->show[y + 1][x] != -2)
			draw_xpm(data, data->field[y + 1][x], x, y + 1);
		if (x + 1 < data->img->how_x && data->show[y + 1][x + 1] != -2)
			draw_xpm(data, data->field[y + 1][x + 1], x + 1, y + 1);
		if (x - 1 >= 0 && data->show[y + 1][x - 1] != -2)
			draw_xpm(data, data->field[y + 1][x - 1], x - 1, y + 1);
	}
	if (x - 1 >= 0 && data->show[y][x - 1] != -2)
		draw_xpm(data, data->field[y][x - 1], x - 1, y);
	if (x + 1 < data->img->how_x && data->show[y][x + 1] != -2)
		draw_xpm(data, data->field[y][x + 1], x + 1, y);
}

void		draw_xpm(t_data *data, int flag, int x, int y)
{
	char path[16];

	if (flag == -2)
		return ;
	if (flag == 9)
		data->show[y][x] = 1;
	if (flag != -1 && flag != 9)
		data->show[y][x] = -2;
	if (flag == 0)
		bfs_zero_show(data, flag, x, y);
	ft_memcpy(&path[0], "./xpm/type .xpm\0", 16);
	if (flag > -2)
	{
		if (flag == -1 || flag == 9)
			path[10] = 'm';
		else if (flag == 10) {
			path[10] = 'n';
		}
		else
			path[10] = flag + 48;
		// ft_printf("%s ", path);
		init_xpm(data->img, data, &path[0]);
		// ft_printf("  [%d:%d]", y, x);
		y = data->img->shifty + y * data->cellsize;
		x = data->img->shiftx + x * data->cellsize;
		// ft_printf("  [%d:%d]\n", y, x);
		data->openc--;
		mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->xpm, x - 1, y - 1);
		if (data->show) {
		int test = 0, test2 = 0;
		for (int i = 0; i < data->img->how_y; ++i)
		{
			for (int j = 0; j < data->img->how_x; ++j)
			{
				if (data->show[i][j] == 1)
					test++;
				if (data->show[i][j] == -2)
					test2++;
			}
		}
		data->openm = test;
		data->openc = test2;
		}
	}
	if (data->openm == data->img->mines && data->openc == data->img->how_x * data->img->how_y - data->img->mines)
		data->status = 3;
}
