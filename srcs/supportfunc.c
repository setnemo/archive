/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supportfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

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
}

void		hook_start_pause(t_data *data)
{
	t_img *img;

	img = data->img;
	if (data->status == 0 || data->status == 2)
	{
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
	int x1, y1;
	// ft_printf("mouse[%d] x[%d] y[%d]\n     X", mouse, x, y);
	x1 = (x - data->img->shiftx) / data->cellsize;
	y1 = (y - data->img->shifty) / data->cellsize;
	if (x1 >= 0 && y1 >= 0 && x1 < data->img->how_x &&
		y1 < data->img->how_y && x >= data->img->shiftx &&
		y >= data->img->shifty)
	{
		if (mouse == 1)
			ft_printf("LEFT CLICK TO CELLS\n");
		if (mouse == 2)
			ft_printf("RIGHT CLICK TO CELLS\n");
		else
			ft_printf("[%d] CLICK TO CELLS\n", mouse);

	}
	if (y >= data->img->button[0] && y <= data->img->button[2] && x >= data->img->button[1] && x <= data->img->button[3])
	{
		hook_start_pause(data);
	}
	ft_printf("mouse[%d] x1[%d] y1[%d]\n", mouse, x, y);
	return (0);
}

int			window_close(void)
{
	exit(1);
	return (0);
}

int			key_hook(int keycode, t_data *data)
{
	ft_printf("HOOK %d\n", keycode);
	if ((keycode == 53 || keycode == 65307) && (data->status == 0 || data->status == 2))
	{
		exit(1);
	}
	else if (keycode == 49)
	{
		hook_start_pause(data);
	}
	return (0);
}

void		init_img(t_data *data)
{
	t_img	*img;
	int		i;

	img = data->img;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, data->windowsizew, data->windowsizeh, "Mines42");
	img->img = mlx_new_image(img->mlx, data->windowsizew, data->windowsizeh);
	img->img_ptr = (int*)mlx_get_data_addr(img->img, &img->bpp, &img->sl, &img->endian);
	img->fillline = mlx_get_color_value(img->mlx, img->fillline);
	i = -1;
	while (++i < data->windowsizew * data->windowsizeh)
	{
		img->img_ptr[i] = 0xc0c0c0;
	}
}
