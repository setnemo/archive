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
		mlx_put_image_to_window(data->img->mlx, img->win, img->smile, img->button[1] - 2, img->button[0] - 2);
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
	
	ft_printf("mouse[%d] x[%d] y[%d]\n", mouse, x, y);
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
		{
			if (data->start == 1)
			{
				// data->time = time(NULL);
				data->start = 2;
				init_play_field(data, x1, y1);
			}
			// ft_printf("LEFT CLICK TO CELLS[%d][%d]          (%d:%d)\n", y1, x1, y, x);
			if (data->start)
			{
				// ft_printf("cell[%d]\n", data->field[y1][x1]);
				if (data->field[y1][x1] != -1)
					draw_xpm(data, data->field[y1][x1], x1, y1);
				else
				{
					draw_xpm(data, data->field[y1][x1], x1, y1);
					// ft_printf("HERAK!\n");
					draw_stop(data, 0);
				}
			}
		}
		if (mouse == 2 || mouse == 3) //linux 3
		{
			if (data->start == 1)
			{
				data->start = 2;
				init_play_field(data, x1, y1);
				draw_xpm(data, data->field[y1][x1], x1, y1);
			}
			else if (data->start == 0)
				return (0);
			// ft_printf("RIGHT CLICK TO CELLS[%d][%d]          (%d:%d)\n", y1, x1, y, x);
			if (data->start)
			{
				// ft_printf("cell[%d]\n", data->field[y1][x1]);
				if (data->show[y1][x1] == 0)
					draw_xpm(data, 9, x1, y1);
				else if (data->show[y1][x1] == 1)
				{
					draw_xpm(data, 10, x1, y1);
					data->show[y1][x1] = 0;
				}
			}
		}
		// if (data->show)
		// {
		// 	ft_printf("========= start show ======\n");
		// 	for (int i = 0; i < data->img->how_y; ++i)
		// 	{
		// 		for (int j = 0; j < data->img->how_x; ++j)
		// 		{
		// 			ft_printf("%d ", data->field[i][j]);
		// 		}
		// 		ft_printf("\n");
		// 	}
		// 	ft_printf("=========  end  show ======\n");
			ft_printf("======= %d ============= %d ====\n", data->openm, data->openc);

		// }
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
	// ft_printf("HOOK %d\n", keycode);
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
			ft_printf("new game....\n");
			t_img *img = data->img;
			data->openc = data->img->how_x * data->img->how_y;
			data->openm = data->img->mines;
			mlx_clear_window (data->img->mlx, data->img->win);
			img->img = mlx_new_image(img->mlx, data->windowsizew, data->windowsizeh);
			img->img_ptr = (int*)mlx_get_data_addr(img->img, &img->bpp, &img->sl, &img->endian);
			int i = -1;
			while (++i < data->windowsizew * data->windowsizeh)
				data->img->img_ptr[i] = 0xc0c0c0;
			init_lines(data->img, data);
			mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
			data->status = 0;
			hook_start_pause(data);
		}
	}
	return (0);
}

