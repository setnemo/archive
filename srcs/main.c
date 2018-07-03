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


int		mouse_hook(int mouse, int x, int y, t_data *data)
{
	int x1, y1;
	// ft_printf("mouse[%d] x[%d] y[%d]\n", mouse, x, y);
	x1 = (x - data->img->shiftx) / data->cellsize;
	y1 = (y - data->img->shifty) / data->cellsize;
	if (x1 >= 0 && y1 >= 0 && x1 < data->img->how_x &&
		y1 < data->img->how_y && x >= data->img->shiftx &&
		y >= data->img->shifty)
	{
		if (mouse == 1)
			ft_printf("LEFT CLICK TO [%d] CELLS\n", g_box[y1][x1]);
		if (mouse == 2)
			ft_printf("RIGHT CLICK TO [%d] CELLS\n", g_box[y1][x1]);
		else
			ft_printf("[%d] CLICK TO [%d] CELLS\n", mouse, g_box[y1][x1]);

	}
	// ft_printf("mouse[%d] x1[%d] y1[%d]\n", mouse, x1, y1);
	return (0);
}

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
	// img->img_ptr[p1[Y] * img->sl / 4 + p1[X1] - 1] = color;
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


// написать инициализацию в зависимости от сложности
// дорисовать кнопку страта в шапке (она же будет выход, если нажат эскейп)
// написать алгоритм игры
// связать кей хуки с отрисовкой
// реализовать свой рандом на базе urandom
// реализовать таймер на базе clock() и отрисовать его в игре




// в коррекшин форме спросить
// 1) автор файл, нормы, define value (mines, size)
// YES/NO
// 2) реализованы ли три сложности игры?
// YES/NO
// 3) попросить студента показать свой рандом на базе urandom
// YES/NO
// 4) проверить, есть ли таймер в игре
// YES/NO
// 5) Проверить, как работают  mouse key hooks \\ возможны срабатывания при наведении чуть выше первой строки игры, и слева от крайнее колонки
// YES/NO
// 6) Для выхода из игры требуется подтверждение, а не по однократному нажатию кнопки ESC
// YES/NO
// 7) При нажатии ESC останавливается таймер? 
// YES/NO


