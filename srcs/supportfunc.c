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

int			window_close(void)
{
	exit(1);
	return (0);
}

int			key_hook(int keycode)
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
	img->img_ptr = mlx_get_data_addr(img->img, &img->bpp, &img->sl,
		&img->endian);
}
