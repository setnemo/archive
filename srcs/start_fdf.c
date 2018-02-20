/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void			move_to_center(t_mlx *data)
{
	float	ratex;
	float	ratey;
	t_map	*lines;

	ratex = (data->window / 2) / data->how_x;
	ratey = (data->window / 2) / data->how_y;
	lines = data->line;
	while (lines)
	{
		lines->px *= ratex;
		lines->py *= ratey;
		lines->px1 *= ratex;
		lines->py1 *= ratey;
		lines->px2 *= ratex;
		lines->py2 *= ratey;
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
	lines = data->line;
	ratex = data->window / 3;
	ratey = data->window / 3;
	while (lines)
	{
		lines->px += ratex;
		lines->py += ratey;
		lines->px1 += ratex;
		lines->py1 += ratey;
		lines->px2 += ratex;
		lines->py2 += ratey;
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
}

static void			brzh1(t_mlx *data, t_brz *brz, int iter, int rate)
{
	mlx_pixel_put(data->mlx, data->win, brz->py, brz->px, brz->pc);
	rate = (brz->dx / 2);
	iter = 1;
	while (iter <= brz->dx)
	{
		brz->py += brz->xinc;
		rate += brz->dy;
		iter++;
		if (rate >= brz->dx)
		{
			rate -= brz->dx;
			brz->px += brz->yinc;
		}
		mlx_pixel_put(data->mlx, data->win, brz->py, brz->px, brz->pc);
	}
}

static void			brzh2(t_mlx *data, t_brz *brz, int iter, int rate)
{
	mlx_pixel_put(data->mlx, data->win, brz->py, brz->px, brz->pc);
	rate = brz->dy / 2;
	iter = 1;
	while (iter <= brz->dy)
	{
		brz->px += brz->yinc;
		rate += brz->dx;
		if ( rate >= brz->dy)
		{
			rate -= brz->dy;
			brz->py += brz->xinc;
		}
		mlx_pixel_put(data->mlx, data->win, brz->py, brz->px, brz->pc);
		iter++;
	}
}

static void			brz_start(t_mlx *data, t_map *lines)
{
	t_brz		brz1;
	t_brz		brz2;

	brz1.py = lines->py;
	brz1.px = lines->px;
	brz1.dx = lines->py1 - lines->py; 
	brz1.dy = lines->px1 - lines->px;
	brz1.xinc = (brz1.dx > 0) ? 1 : -1;
	brz1.yinc = (brz1.dy > 0 ) ? 1 : -1;
	brz1.dx = abs(brz1.dx); 
	brz1.dy = abs(brz1.dy);
	brz1.pc = (lines->pc == 0) ? data->fill : lines->pc;
	brz2.py = lines->py;
	brz2.px = lines->px;
	brz2.dx = lines->py2 - lines->py; 
	brz2.dy = lines->px2 - lines->px;
	brz2.xinc = (brz2.dx > 0) ? 1 : -1;
	brz2.yinc = (brz2.dy > 0 ) ? 1 : -1;
	brz2.dx = abs(brz2.dx); 
	brz2.dy = abs(brz2.dy);
	brz2.pc = (lines->pc == 0) ? data->fill : lines->pc;
	brz1.dx > brz1.dy ? brzh1(data, &brz1, 0, 0) : brzh2(data, &brz1, 0, 0);
	brz2.dx > brz2.dy ? brzh1(data, &brz2, 0, 0) : brzh2(data, &brz2, 0, 0);
}


void				start_fdf(t_mlx *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->window, data->window, "FDF");
	move_to_center(data);
	t_map *lines = data->line;
	int i = 1;
	while (lines)
	{
		//proection(lines);
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
	while (lines)
	{
		brz_start(data, lines);
	//	printf(":ШШШ:lines->px lines->py lines->px1 lines->py1 lines->px2 lines->py2 lines->pz lines->pc\n");
		printf("%f		%f		%f		%f		%f		%f\n",i, lines->px, lines->py,lines->px1, lines->py1,lines->px2, lines->py2);
//		printf(" %i         %f         %f       %f         %f         %f          %f        %f        %lu\n",i, lines->px, lines->py,lines->px1, lines->py1,lines->px2, lines->py2,lines->pz,lines->pc);
		i++;
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
	mlx_loop(data->mlx);
}

