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
		mlx_put_image_to_window(img->mlx, img->win, img->smile, img->button[1] - 2, img->button[0] - 2);
	}
	else if (data->status == 1)
	{
		data->status = 2;
		init_button(img, data, "./xpm/Sleepy.xpm");
		mlx_put_image_to_window(img->mlx, img->win, img->smile, img->button[1] - 2, img->button[0] - 2);
	}
}


int		mouse_hook(int mouse, int x, int y, t_data *data)
{
	int x1;
	int y1;
	// ft_printf("mouse[%d] x[%d] y[%d]\n     X", mouse, x, y);
	x1 = (x - data->img->shiftx) / data->cellsize;
	y1 = (y - data->img->shifty) / data->cellsize;
	if (x1 >= 0 && y1 >= 0 && x1 < data->img->how_x &&
		y1 < data->img->how_y && x >= data->img->shiftx &&
		y >= data->img->shifty)
	{
		if (mouse == 1)
		{
			if (data->start == 1)
			{
				data->start = 2;
				init_play_field(data, x1, y1);
			}
			ft_printf("LEFT CLICK TO CELLS[%d][%d]          (%d:%d)\n", y1, x1, y, x);
			if (data->start)
			{
				ft_printf("cell[%d]\n", data->field[y1][x1]);
				draw_xpm(data, data->field[y1][x1], x1, y1);
			}
		}
		if (mouse == 2)
		{
			draw_xpm(data, 9, x1, y1);
			ft_printf("RIGHT CLICK TO CELLS[%d][%d]\n", y1, x1);
		}
		// else
		// 	ft_printf("[%d] CLICK TO CELLS\n", mouse);

	}
	if (y >= data->img->button[0] && y <= data->img->button[2] && x >= data->img->button[1] && x <= data->img->button[3])
	{
		hook_start_pause(data);
	}
	// ft_printf("mouse[%d] x1[%d] y1[%d]\n", mouse, x, y);
	return (0);
}

int			key_hook(int keycode, t_data *data)
{
	ft_printf("HOOK %d\n", keycode);
	if ((keycode == 53 || keycode == 65307) && (data->status == 0 || data->status == 2))
	{
		exit(1);
	}
	else if (keycode == 49 || keycode == 32)
	{
		hook_start_pause(data);
	}
	return (0);
}

