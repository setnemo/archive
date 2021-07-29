/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

static void	free_field_and_show(t_data *data, int i)
{
	while (++i < data->img->how_y)
	{
		free(data->field[i]);
		free(data->show[i]);
	}
	free(data->field);
	free(data->show);
	data->show = NULL;
}

static void	drow_stop_additional(t_data *data, char *gameover, char *button)
{
	int		i1;
	int		i2;

	i1 = 120;
	i2 = 72;
	data->img->xpm = mlx_xpm_file_to_image(data->img->mlx, gameover, &i1, &i2);
	i2 = (data->windowsizeh / 2) - 36;
	i1 = (data->windowsizew / 2) - 60;
	mlx_put_image_to_window(data->img->mlx, data->img->win,
		data->img->xpm, i1, i2);
	data->start = 1;
	free_field_and_show(data, -1);
	init_button(data->img, data, button);
	mlx_put_image_to_window(data->img->mlx, data->img->win,
		data->img->smile, data->img->button[1] - 2, data->img->button[0] - 2);
	mlx_destroy_image(data->img->mlx, data->img->img);
	data->status = 3;
}

void		draw_stop(t_data *data, int flag)
{
	char	*gameover;
	char	*button;

	if (flag)
	{
		gameover = "./xpm/win.xpm";
		button = "./xpm/Love.xpm";
	}
	else
	{
		gameover = "./xpm/lose.xpm";
		button = "./xpm/Sad.xpm";
	}
	drow_stop_additional(data, &gameover[0], &button[0]);
}

void		draw_square(t_img *img, t_data *data, int points[])
{
	int temp;

	temp = points[1];
	while (points[0] != points[2] - 1)
	{
		points[1] = temp;
		while (points[1] != points[3] - 1)
		{
			img->img_ptr[points[0] * img->sl / 4 +
				points[1] - 1] = data->img->fillline;
			points[1]++;
		}
		points[0]++;
	}
}
