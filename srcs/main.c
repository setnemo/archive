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

char	g_box[10][10] = {
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48},
	{48, 48, 48, 48, 48, 48, 48, 48, 48, 48}
	};

void	put_pxl_to_img(t_img *img, int x, int y, int color)
{
	if (x || y || color)
	// color = mlx_get_color_value(img->mlx, color);
	img->img_ptr[y * img->sl / 4 + x] = color;
}

void		start_mines(t_data *data)
{
	init_img(data);
	int i = -1, j = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
		{
			put_pxl_to_img(data->img, i*10, j*10, 0xFFFFFF);
		}
	}
	mlx_put_image_to_window(data->img->mlx, data->img->win, data->img->img, 0, 0);
	mlx_hook(data->img->win, 17, 0L, window_close, data);
	mlx_key_hook(data->img->win, key_hook, data);
	mlx_loop(data->img->mlx);
}

int			main(void)
{
	t_data	data;
	t_img	img;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&img, sizeof(t_img));
	data.img = &img;
	start_mines(&data);
	return (0);
}
