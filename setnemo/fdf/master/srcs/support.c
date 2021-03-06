/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		colorize(t_mlx *data, int flag)
{
	t_map *lines;

	lines = data->line;
	while (lines)
	{
		if (flag == 1)
		{
			if (lines->z > 0)
				lines->pc = 0xfbba00;
			if (lines->z < 0)
				lines->pc = 0x0033FF;
			if (lines->z == 0)
				lines->pc = data->fill;
		}
		else
			lines->pc = data->fill;
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
}

static void	scale_color_show_key(int k, t_mlx *data)
{
	if (k == 61)
		scale(data, 1);
	if (k == 45)
		scale(data, 2);
	if (k == 101)
	{
		if (data->coloriz == 1)
			data->coloriz = 0;
		else
			data->coloriz = 1;
		colorize(data, data->coloriz);
	}
	if (k == 114)
	{
		if (data->show == 1)
			data->show = 0;
		else
			data->show = 1;
	}
}

static void	rotate_key(int k, t_mlx *data)
{
	if (k == 65362)
	{
		data->radx += 0.0125;
		rotate_fdf(data, 0);
	}
	if (k == 65364)
	{
		data->radx -= 0.0125;
		rotate_fdf(data, 0);
	}
	if (k == 65361)
	{
		data->rady += 0.0125;
		rotate_fdf(data, 1);
	}
	if (k == 65363)
	{
		data->rady -= 0.0125;
		rotate_fdf(data, 1);
	}
}

static void	move_key(int k, t_mlx *data)
{
	if (k == 113)
	{
		data->radx = 0;
		data->rady = 0;
		data->move = 0;
	}
	if (k == 119)
		data->move = 4;
	if (k == 115)
		data->move = 2;
	if (k == 97)
		data->move = 3;
	if (k == 100)
		data->move = 1;
}

int			deal_key(int k, t_mlx *data)
{
	if (k == 65307)
	{
		free_data(data, 0);
		exit(0);
	}
	if (k >= 65361 && k <= 65364)
		rotate_key(k, data);
	if (k == 113 || k == 119 || k == 115 || k == 97 || k == 100)
		move_key(k, data);
		scale_color_show_key(k, data);
	if (k >= 1 && k <= 66666)
	{
		mlx_clear_window(data->mlx, data->win);
		start_fdf(data);
	}
	//ft_testintstr(k, "????????????");
	return (k);
}
