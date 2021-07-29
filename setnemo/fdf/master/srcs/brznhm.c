/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brznhm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			brzh1(t_mlx *data, t_brz *brz, int iter, int rate)
{
	mlx_pixel_put(data->mlx, data->win, brz->px, brz->py, brz->pc);
	rate = (brz->dx / 2);
	iter = 1;
	while (iter <= brz->dx)
	{
		brz->px += brz->xinc;
		rate += brz->dy;
		iter++;
		if (rate >= brz->dx)
		{
			rate -= brz->dx;
			brz->py += brz->yinc;
		}
		mlx_pixel_put(data->mlx, data->win, brz->px, brz->py, brz->pc);
	}
}

static void			brzh2(t_mlx *data, t_brz *brz, int iter, int rate)
{
	mlx_pixel_put(data->mlx, data->win, brz->px, brz->py, brz->pc);
	rate = brz->dy / 2;
	iter = 1;
	while (iter <= brz->dy)
	{
		brz->py += brz->yinc;
		rate += brz->dx;
		if (rate >= brz->dy)
		{
			rate -= brz->dy;
			brz->px += brz->xinc;
		}
		mlx_pixel_put(data->mlx, data->win, brz->px, brz->py, brz->pc);
		iter++;
	}
}

static t_map		*while_temp(t_map *temp, int how)
{
	int i;

	i = 0;
	while (i < how)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

static void			brz_core(t_mlx *data, t_map *lines, int flag)
{
	t_brz		brz1;
	t_map		*temp;

	temp = lines;
	brz1.py = lines->py * data->zoomnew + data->shifty;
	brz1.px = lines->px * data->zoomnew + data->shiftx;
	if (flag == 1 || flag == 0)
	{
		brz1.dx = (flag == 1) ? lines->next->px - lines->px : 0;
		brz1.dy = (flag == 1) ? lines->next->py - lines->py : 0;
	}
	else if (flag == 2)
	{
		temp = while_temp(temp, data->how_x);
		brz1.dx = temp->px - lines->px;
		brz1.dy = temp->py - lines->py;
	}
	brz1.xinc = (brz1.dx > 0) ? 1 : -1;
	brz1.yinc = (brz1.dy > 0) ? 1 : -1;
	brz1.dx = abs(brz1.dx);
	brz1.dy = abs(brz1.dy);
	brz1.pc = (lines->pc == 0 && data->coloriz == 0) ? data->fill : lines->pc;
	brz1.dx > brz1.dy ? brzh1(data, &brz1, 0, 0) : brzh2(data, &brz1, 0, 0);
}

void				brz_start(t_mlx *data, t_map *lines, int y, int x)
{
	if (x + 1 < data->how_x)
		brz_core(data, lines, 1);
	else
		brz_core(data, lines, 0);
	if (y + 1 < data->how_y)
		brz_core(data, lines, 2);
	else
		brz_core(data, lines, 0);
}
