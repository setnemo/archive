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

int			window_close(void)
{
	exit(1);
	return (0);
}

static void	start_mines(t_data *data)
{
	t_img *img;

	init_img(data);
	img = data->img;
	init_lines(img, data);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	mlx_put_image_to_window(img->mlx, img->win, img->smile, img->button[1] - 2, img->button[0] - 2);
	mlx_mouse_hook(img->win, mouse_hook, data);
	mlx_hook(img->win, 17, 0, window_close, data);
	mlx_key_hook(img->win, key_hook, data);
	init_play_field(data);
	draw_mines(data);
	mlx_loop(img->mlx);
}

static void	init_struct(t_data *data, int flag)
{
	if (flag)
	{
		data->img->how_x = (flag == 1) ? INTER_SIDE : EXPERT_SIDE_X;
		data->img->how_y = (flag == 1) ? INTER_SIDE : EXPERT_SIDE_Y;
		data->img->mines = (flag == 1) ? INTER_MINES : EXPERT_MINES;
	}
	else
	{
		data->img->how_x = NOVICE_SIDE;
		data->img->how_y = NOVICE_SIDE;
		data->img->mines = NOVICE_MINES;
	}
	data->cellsize = 24;
	data->bordersize = 18;
	data->headersize = 40;
	data->windowsizew = data->bordersize * 2 + (data->img->how_x * data->cellsize);
	data->windowsizeh = data->bordersize * 3 + (data->img->how_y * data->cellsize) + data->headersize;
	data->img->fillline = 0x808080;
	data->img->shifty = data->bordersize * 2 + data->headersize;
	data->img->shiftx = data->bordersize;
	data->img->button[0] = ((data->bordersize * 2 + data->headersize) / 2) - data->cellsize;
	data->img->button[1] = (data->windowsizew / 2) - data->cellsize;
	data->img->button[2] = data->img->button[0] + data->cellsize * 2;
	data->img->button[3] = data->img->button[1] + data->cellsize * 2;
	data->status = 0;
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
		init_struct(&data, 0);
		start_mines(&data);
	}
	else if (argc == 2 && ft_strequ(argv[1], "inter"))
	{
		init_struct(&data, 1);
		start_mines(&data);
	}
	else if (argc == 2 && ft_strequ(argv[1], "expert"))
	{
		init_struct(&data, 2);
		start_mines(&data);
	}
	else
		ft_printf("USAGE MOTHERFUKER!!!!111\n");
	return (0);
}


// DONE 		написать инициализацию в зависимости от сложности
// DONE			дорисовать кнопку страта в шапке (она же будет выход, если нажат эскейп)
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


