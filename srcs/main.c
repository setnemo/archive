/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

char	g_box[9][9] = {
	{0, 1, 2, 3, 4, 5, 6, 7, 8},
	{10, 11, 12, 13, 14, 15, 16, 17, 18},
	{20, 21, 22, 23, 24, 25, 26, 27, 28},
	{30, 31, 32, 33, 34, 35, 36, 37, 38},
	{40, 41, 42, 43, 44, 45, 46, 47, 48},
	{50, 51, 52, 53, 54, 55, 56, 57, 58},
	{60, 61, 62, 63, 64, 65, 66, 67, 68},
	{70, 71, 72, 73, 74, 75, 76, 77, 78},
	{80, 81, 82, 83, 84, 85, 86, 87, 88}
	};

// void	put_pxl_to_img(t_img *img, int x, int y, int color)
// {
// 	if (x || y || color)
// 	color = mlx_get_color_value(img->mlx, color);
	
// }

int		mouse_hook(int x, int y, int z)
{
	ft_printf("mouse[%d] x[%d] y[%d]\n", x, y, z);
	return (0);
}

void		draw_square(t_img *img, t_data *data, int points[])
{
	ft_printf("points[%d][%d][%d][%d]\n", points[0],  points[1],  points[2],  points[3]);
	int temp[4];

	ft_memcpy(&temp[0], &points[0], sizeof(int) * 4);
	while (points[0] != points[2] - 1)
	{
		points[1] = temp[1];
		while (points[1] != points[3] - 1)
		{
			img->img_ptr[points[0] * img->sl / 4 + points[1] - 1] = data->img->fillline;
			points[1]++;
		}
		points[0]++;
	}
	// img->img_ptr[p1[Y] * img->sl / 4 + p1[X] - 1] = color;
}

void		init_lines(t_img *img, t_data *data)
{
	int i;
	int j;
	int points[4];

	j = -1;
	while (++j < img->how_y)
	{
		i = -1;
		while (++i < img->how_x)
		{
			points[0] = data->img->shifty + i * data->cellsize;
			points[1] = data->img->shiftx + j * data->cellsize;
			points[2] = data->img->shifty + (i + 1) * data->cellsize;
			points[3] = data->img->shiftx + (j + 1) * data->cellsize;
			draw_square(img, data, points);
		}
	}
}

void		start_mines(t_data *data)
{
	t_img *img;

	init_img(data);
	img = data->img;
	init_lines(img, data);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	// mlx_hook(img->win, 6, 1L < 6, mouse_hook, data);
	mlx_mouse_hook(img->win, mouse_hook, data);
	mlx_hook(img->win, 17, 0L, window_close, data);
	mlx_key_hook(img->win, key_hook, data);
	mlx_loop(img->mlx);
}

int			main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&img, sizeof(t_img));
	data.img = &img;
	if (argc == 1 && argv)
	{
		data.cellsize = 24;
		data.bordersize = 18;
		data.headersize = 40;
		data.img->how_x = 9;
		data.img->how_y = 9;
		data.windowsizew = data.bordersize * 2 + data.img->how_x * data.cellsize;
		data.windowsizeh = data.bordersize * 3 + data.img->how_y * data.cellsize + data.headersize;
		data.img->fillline = 0x808080;
		data.img->shifty = data.bordersize * 2 + data.headersize;
		data.img->shiftx = data.bordersize;
	}
	start_mines(&data);
	return (0);
}
