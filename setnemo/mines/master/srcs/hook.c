/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

void		hook_start_pause(t_data *data)
{
	t_img *img;

	img = data->img;
	if (data->status == 0 || data->status == 2)
	{
		if (data->status == 0)
			data->start = 1;
		data->status = 1;
		init_button(img, data, "./xpm/Mad.xpm");
		mlx_put_image_to_window(data->img->mlx, img->win,
			img->smile, img->button[1] - 2, img->button[0] - 2);
	}
	else if (data->status == 1)
	{
		data->status = 2;
		init_button(img, data, "./xpm/Sleepy.xpm");
		mlx_put_image_to_window(img->mlx, img->win,
			img->smile, img->button[1] - 2, img->button[0] - 2);
	}
}

static void	mouse_hook_one(int x1, int y1, t_data *data)
{
	if (data->start == 1)
	{
		data->start = 2;
		init_play_field(data, x1, y1);
	}
	if (data->start)
	{
		if (data->field[y1][x1] != -1)
			draw_xpm(data, data->field[y1][x1], x1, y1);
		else
		{
			draw_xpm(data, data->field[y1][x1], x1, y1);
			draw_stop(data, 0);
		}
	}
}

static int	mouse_hook_two(int x1, int y1, t_data *data)
{
	if (data->start == 1)
	{
		data->start = 2;
		init_play_field(data, x1, y1);
		draw_xpm(data, data->field[y1][x1], x1, y1);
	}
	else if (data->start == 0)
		return (1);
	if (data->start)
	{
		if (data->show[y1][x1] == 0)
			draw_xpm(data, 9, x1, y1);
		else if (data->show[y1][x1] == 1)
		{
			draw_xpm(data, 10, x1, y1);
			data->show[y1][x1] = 0;
		}
	}
	return (0);
}

int			mouse_hook(int mouse, int x, int y, t_data *data)
{
	int x1;
	int y1;

	if (data->status == 3)
	{
		key_hook(49, data);
		return (0);
	}
	x1 = (x - data->img->shiftx) / data->cellsize;
	y1 = (y - data->img->shifty) / data->cellsize;
	if (x1 >= 0 && y1 >= 0 && x1 < data->img->how_x &&
		y1 < data->img->how_y && x >= data->img->shiftx &&
		y >= data->img->shifty && data->status == 1)
	{
		if (mouse == 1)
			mouse_hook_one(x1, y1, data);
		if (mouse == 2)
			if (mouse_hook_two(x1, y1, data))
				return (0);
	}
	if (y >= data->img->button[0] && y <= data->img->button[2] &&
		x >= data->img->button[1] && x <= data->img->button[3])
		hook_start_pause(data);
	return (0);
}

int			key_hook(int keycode, t_data *data)
{
	if (data->status != 3)
	{
		if ((keycode == 53 || keycode == 65307) && data->status != 1)
		{
			exit(1);
		}
		else if (keycode == 49 || keycode == 32)
		{
			hook_start_pause(data);
		}
	}
	else
	{
		if (keycode == 53 || keycode == 65307)
		{
			exit(1);
		}
		if (keycode == 49 || keycode == 32)
		{
			restart(data);
		}
	}
	return (0);
}
