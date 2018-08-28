/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
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

void		init_lines(t_img *img, t_data *data)
{
	int i;
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
	init_button(img, data, "./xpm/Shout.xpm");
}

void		init_img(t_data *data)
{
	t_img	*img;
	int		i;

	img = data->img;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx,
		data->windowsizew, data->windowsizeh, "Mines42");
	img->img = mlx_new_image(img->mlx,
		data->windowsizew, data->windowsizeh);
	img->img_ptr = (int*)mlx_get_data_addr(img->img,
		&img->bpp, &img->sl, &img->endian);
	img->fillline = mlx_get_color_value(img->mlx, img->fillline);
	i = -1;
	while (++i < data->windowsizew * data->windowsizeh)
	{
		img->img_ptr[i] = 0xc0c0c0;
	}
}
