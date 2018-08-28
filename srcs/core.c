/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

static void	increment_neighbor(int y, int x, t_data *data)
{
	if (y - 1 >= 0)
	{
		if (data->field[y - 1][x] != -1)
			data->field[y - 1][x]++;
		if (x + 1 < data->img->how_x && data->field[y - 1][x + 1] != -1)
			data->field[y - 1][x + 1]++;
		if (x - 1 >= 0 && data->field[y - 1][x - 1] != -1)
			data->field[y - 1][x - 1]++;
	}
	if (y + 1 < data->img->how_y)
	{
		if (data->field[y + 1][x] != -1)
			data->field[y + 1][x]++;
		if (x + 1 < data->img->how_x && data->field[y + 1][x + 1] != -1)
			data->field[y + 1][x + 1]++;
		if (x - 1 >= 0 && data->field[y + 1][x - 1] != -1)
			data->field[y + 1][x - 1]++;
	}
	if (x - 1 >= 0 && data->field[y][x - 1] != -1)
		data->field[y][x - 1]++;
	if (x + 1 < data->img->how_x && data->field[y][x + 1] != -1)
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
				increment_neighbor(i, j, data);
			}
		}
	}
}

void		restart(t_data *data)
{
	int		i;
	t_img	*img;

	i = -1;
	img = data->img;
	data->openc = data->img->how_x * data->img->how_y;
	data->openm = data->img->mines;
	mlx_clear_window(data->img->mlx, data->img->win);
	img->img = mlx_new_image(img->mlx, data->windowsizew, data->windowsizeh);
	img->img_ptr = (int*)mlx_get_data_addr(img->img,
		&img->bpp, &img->sl, &img->endian);
	while (++i < data->windowsizew * data->windowsizeh)
		data->img->img_ptr[i] = 0xc0c0c0;
	init_lines(data->img, data);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	data->status = 0;
	hook_start_pause(data);
}
