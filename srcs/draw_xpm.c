/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

void		init_xpm(t_img *img, t_data *data, char *str)
{
	int		i1;
	int		i2;

	i1 = data->cellsize;
	i2 = data->cellsize;
	img->xpm = mlx_xpm_file_to_image(img->mlx, str, &i1, &i2);
}

void		bfs_zero_show(t_data *data, int x, int y)
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

static void	draw_xpm_if_flag(t_data *data, int flag, char *path)
{
	if (flag == -1 || flag == 9)
		path[10] = 'm';
	else if (flag == 10)
	{
		data->openc += 2;
		data->openm++;
		path[10] = 'n';
	}
	else
		path[10] = flag + 48;
	init_xpm(data->img, data, &path[0]);
	data->openc--;
}

void		draw_xpm(t_data *data, int flag, int x, int y)
{
	char path[16];

	if (flag == -2)
		return ;
	if (flag == 9)
	{
		data->openm--;
		data->show[y][x] = 1;
	}
	if (flag != -1 && flag != 9)
		data->show[y][x] = -2;
	if (flag == 0)
		bfs_zero_show(data, x, y);
	ft_memcpy(&path[0], "./xpm/type .xpm\0", 16);
	if (flag > -2)
	{
		draw_xpm_if_flag(data, flag, &path[0]);
		y = data->img->shifty + y * data->cellsize;
		x = data->img->shiftx + x * data->cellsize;
		mlx_put_image_to_window(data->img->mlx, data->img->win,
			data->img->xpm, x - 1, y - 1);
	}
	if (data->openc == 0 && data->openm == 0)
		draw_stop(data, 1);
}
