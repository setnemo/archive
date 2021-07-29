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
	system("leaks -quiet mines42");
	exit(1);
	return (0);
}

int	gameloop(t_data *data)
{
	
	if (data->status == 0)
	{
		// ft_printf("---0s---");
		init_img(data);
		// ft_printf(".");
		init_button(data->img, data, "./xpm/Shout.xpm");
		// ft_printf("---0e---");
	}
	else if (data->status == 1)
	{
		// ft_printf("---1s---");
		init_img(data);
		init_button(data->img, data, "./xpm/Mad.xpm");
		// ft_printf("-");
		// ft_printf("---1e---");
		if (data->show)
		{
			for (int i = 0; i < data->img->how_y; ++i)
			{
				for (int j = 0; j < data->img->how_x; ++j)
				{
					// if ()
					draw_xpm(data, data->field[i][j], j, i);
				}
			}
			
		}

	}
	else if (data->status == 3 || data->status == 4)
	{
		int		i1;
		int		i2;
		char	*gameover;
		char	*button;

		i1 = 120;
		i2 = 72;
		if (data->status == 3)
		{
			gameover = "./xpm/win.xpm";
			button = "./xpm/Love.xpm";
		}
		else
		{
			gameover = "./xpm/lose.xpm" ;
			button = "./xpm/Sad.xpm" ;
			
		}
		data->img->xpm = mlx_xpm_file_to_image(data->img->mlx, gameover, &i1, &i2);
		i2 = (data->windowsizeh / 2) - 36;
		i1 = (data->windowsizew / 2) - 60;
		mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->xpm, i1, i2);
		// data->start = 1;
		int i;
		i = -1;
		// ft_printf("---34s---\n");
		if (data->show) {
			while (++i < data->img->how_y)
			{
						// ft_printf("=%i=========>%p\n===========>%p\n", i, data->field[i], data->show[i]);

				free(data->field[i]);
				free(data->show[i]);
			}
			// ft_printf("---34se---\n");
						// ft_printf("===========>%p\n===========>%p\n", data->field, data->show);
			free(data->field);
			free(data->show);
			data->show = 0;
		}
		// data->show = NULL;
		init_button(data->img, data, button);
		// data->start = 0;
		// mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->smile, data->img->button[1] - 2, data->img->button[0] - 2);
		// mlx_destroy_image(data->img->mlx, data->img->img);
		// ft_printf("---34e---");		// init_img(data);

	}
	else if (data->status == 2)
	{
		// ft_printf("---2s---");		// init_img(data);
		init_img(data);
		init_button(data->img, data, "./xpm/Sleepy.xpm");
		// ft_printf("+");
		// ft_printf("---2e---");		// init_img(data);
	}
	return (1);
}

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
	mlx_put_image_to_window(data->img->mlx, img->win, img->smile, img->button[1] - 2, img->button[0] - 2);
}

void		init_lines(t_img *img, t_data *data)
{
	int		i;
	i = -1;
	while (++i < data->windowsizew * data->windowsizeh)
	{
		// ft_printf(":%i:\n", i);
		img->img_ptr[i] = 0xc0c0c0;
	}
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
}

void		init_img(t_data *data)
{
	t_img	*img;


	img = data->img;
	mlx_clear_window(data->img->mlx, data->img->win);
	if (data->img->img)
		mlx_destroy_image(data->img->mlx, data->img->img);
	if (data->img->smile)
		mlx_destroy_image(data->img->mlx, data->img->smile);
	data->img->img = mlx_new_image(data->img->mlx, data->windowsizew, data->windowsizeh);
	init_lines(data->img, data);
	mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->img, 0, 0);

}


static void	start_mines(t_data *data)
{
	t_img *img;

	img = data->img;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, data->windowsizew, data->windowsizeh, "Mines42");
	data->img->img = mlx_new_image(data->img->mlx, data->windowsizew, data->windowsizeh);
	img->img_ptr = (int*)mlx_get_data_addr(img->img, &img->bpp, &img->sl, &img->endian);
	img->fillline = mlx_get_color_value(img->mlx, img->fillline);
	init_lines(data->img, data);
	mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->img, 0, 0);
	mlx_mouse_hook(data->img->win, mouse_hook, data);
	mlx_hook(data->img->win, 17, 0, window_close, data);
	mlx_key_hook(data->img->win, key_hook, data);
	mlx_loop_hook(data->img->mlx, gameloop, data);
	// ft_printf("%lld", clock());
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
	data->start = 0;
	data->openc = 0;
	data->openm = 0;
	data->show = 0;
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
// DONE			написать алгоритм игры
// DONE		 	связать кей хуки с отрисовкой
// DONE			реализовать свой рандом на базе urandom
// реализовать таймер на базе clock() и отрисовать его в игре




// в коррекшин форме спросить
// 1) автор файл, нормы, define value (mines, size)
// YES/NO
// 2) реализованы ли три сложности игры?
// YES/NO
// 3) попросить студента показать свой рандом на базе urandom
// YES/NO
// 4) Проверить, как работают  mouse key hooks \\ возможны срабатывания при наведении чуть выше первой строки игры, и слева от крайнее колонки
// YES/NO
// 5) Для выхода из игры требуется подтверждение, а не по однократному нажатию кнопки ESC
// YES/NO
// 6) проверить, есть ли таймер в игре
// YES/NO
// 7) При нажатии ESC останавливается таймер? 
// YES/NO


