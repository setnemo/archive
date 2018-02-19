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

// static void			brz2(t_mlx *data, t_map *lines, int i, int rate)
// {
// 	int dx;
// 	int dy;
// 	int xinc;
// 	int yinc;

// 	dx = lines->py2 - lines->py;
// 	dy = lines->px2 - lines->px;
// 	xinc = ( dx > 0 ) ? 1 : -1;
// 	yinc = ( dy > 0 ) ? 1 : -1;
// 	dx = ABS(dx);
// 	dy = ABS(dy);
// 	mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
// 	if ( dx > dy )
// 	{
// 		rate = (dx / 2);
// 		i = 1;
// 		while (i <= dx)
// 		{
// 			lines->py += xinc;
// 			rate += dy;
// 			i++;
// 			if (rate >= dx)
// 			{
// 				rate -= dx;
// 				lines->px += yinc;
// 			}
// 			mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
// 		}
// 	}
// 	else
// 	{
// 		rate = dy / 2;
// 		i = 1;
// 		while (i <= dy)
// 		{
// 			lines->px += yinc ;
// 			rate += dx;
// 			if ( rate >= dy)
// 			{
// 				rate -= dy;
// 				lines->py += xinc;
// 			}
// 			mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
// 			i++;
// 		}
// 	}
// }


// static void			brz1(t_mlx *data, t_map *lines, int i1, int rate1)
// {
// 	int dx;
// 	int dy;
// 	int xinc;
// 	int yinc;

// 	dx = lines->py1 - lines->py;
// 	dy = lines->px1 - lines->px;
// 	xinc = ( dx > 0 ) ? 1 : -1;
// 	yinc = ( dy > 0 ) ? 1 : -1;
// 	dx = ABS(dx);
// 	dy = ABS(dy);
// 	mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
// 	if ( dx > dy )
// 	{
// 		rate1 = (dx / 2);
// 		i1 = 1;
// 		while (i1 <= dx)
// 		{
// 			lines->py += xinc;
// 			rate1 += dy;
// 			i1++;
// 			if (rate1 >= dx)
// 			{
// 				rate1 -= dx;
// 				lines->px += yinc;
// 			}
// 			mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
// 		}
// 	}
// 	else
// 	{
// 		rate1 = dy / 2;
// 		i1 = 1;
// 		while (i1 <= dy)
// 		{
// 			lines->px += yinc ;
// 			rate1 += dx;
// 			if ( rate1 >= dy)
// 			{
// 				rate1 -= dy;
// 				lines->py += xinc;
// 			}
// 			mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
// 			i1++;
// 		}
// 	}
// }



static void			move_to_center(t_mlx *data)
{
	float	ratex;
	float	ratey;
	t_map	*lines;

	lines = data->line;
	ratex = (data->window - (data->window / 5)) / data->how_x;
	ratey = (data->window - (data->window / 5)) / data->how_y;
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
	ratex = (data->window / data->how_x)/3;
	ratey = (data->window / data->how_y)/3;
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

static void			brzh(t_mlx *data, t_brz *brz, int iter, int rate)
{
	mlx_pixel_put(data->mlx, data->win, brz->py, brz->px, brz->pc);
	if (brz->dx > brz->dy)
	{
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
	else
	{
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
	brz1.dx = ABS(brz1.dx); 
	brz1.dy = ABS(brz1.dy);
	brz1.pc = (lines->pc == 0) ? data->fill : lines->pc;
	brz2.py = lines->py;
	brz2.px = lines->px;
	brz2.dx = lines->py2 - lines->py; 
	brz2.dy = lines->px2 - lines->px;
	brz2.xinc = (brz2.dx > 0) ? 1 : -1;
	brz2.yinc = (brz2.dy > 0 ) ? 1 : -1;
	brz2.dx = ABS(brz2.dx); 
	brz2.dy = ABS(brz2.dy);
	brz2.pc = (lines->pc == 0) ? data->fill : lines->pc;
	brzh(data, &brz1, 0, 0);
	brzh(data, &brz2, 0, 0);
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
		// lines->pc = data->fill;
//		if (lines->flag1 == 1)
		// float tempx = lines->px;
		// float tempy = lines->py;
			brz_start(data, lines);
//		if (lines->flag2 == 1)
			// lines->px = tempx;
			// lines->py = tempy;
			// brz2(data, lines, 0, 0);
		printf("\n........lines->flag1 == |%i| lines->flag2 == |%i|\n\n", lines->flag1, lines->flag2);
		ft_printf(":ШШШ:lines->px lines->py lines->px1 lines->py1 lines->px2 lines->py2 lines->pz lines->pc\n");
		printf(" %i         %f         %f       %f         %f         %f          %f        %f        %lu\n",i, lines->px, lines->py,lines->px1, lines->py1,lines->px2, lines->py2,lines->pz,lines->pc);
		i++;
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
		mlx_loop(data->mlx);
	// lines = data->line;
	// while (lines)
	// {
	// 	printf("lines\n");

	// 	if (lines->next)
	// 		lines = lines->next;
	// 	else
	// 		break ;
	// }
}

