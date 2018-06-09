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
#define SIZEW 1000
#define SIZEH 500

int			window_close(void)
{
	exit(1);
	return (0);
}

int		key_hook(int keycode)
{
	if (keycode == 53)
		exit(1);
	return (0);
}

void		init_img(t_data *data)
{
	t_img	*img;

	img = data->img;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, SIZEW, SIZEH, "Mines42");
	img->img = mlx_new_image(img->mlx, SIZEW, SIZEH);
	img->img_ptr = mlx_get_data_addr(img->img,
			&img->bpp, &img->sl, &img->endian);
}

void		start_mines(t_data *data)
{
	init_img(data);
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
