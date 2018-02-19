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

int ft_abs(int x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

static void			brz2(t_mlx *data, t_map *lines, int i, int rate)
{
	int dx;
	int dy;
	int xinc;
	int yinc;

	dx = lines->py2 - lines->py;
	dy = lines->px2 - lines->px;
	xinc = ( dx > 0 ) ? 1 : -1;
	yinc = ( dy > 0 ) ? 1 : -1;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
	mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
	if ( dx > dy )
	{
		rate = (dx / 2);
		i = 1;
		while (i <= dx)
		{
			lines->py += xinc;
			rate += dy;
			i++;
			if (rate >= dx)
			{
				rate -= dx;
				lines->px += yinc;
			}
			mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
		}
	}
	else
	{
		rate = dy / 2;
		i = 1;
		while (i <= dy)
		{
			lines->px += yinc ;
			rate += dx;
			if ( rate >= dy)
			{
				rate -= dy;
				lines->py += xinc;
			}
			mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
			i++;
		}
	}
}


static void			brz1(t_mlx *data, t_map *lines, int i1, int rate1)
{
	int dx;
	int dy;
	int xinc;
	int yinc;

	dx = lines->py1 - lines->py;
	dy = lines->px1 - lines->px;
	xinc = ( dx > 0 ) ? 1 : -1;
	yinc = ( dy > 0 ) ? 1 : -1;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
	mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
	if ( dx > dy )
	{
		rate1 = (dx / 2);
		i1 = 1;
		while (i1 <= dx)
		{
			lines->py += xinc;
			rate1 += dy;
			i1++;
			if (rate1 >= dx)
			{
				rate1 -= dx;
				lines->px += yinc;
			}
			mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
		}
	}
	else
	{
		rate1 = dy / 2;
		i1 = 1;
		while (i1 <= dy)
		{
			lines->px += yinc ;
			rate1 += dx;
			if ( rate1 >= dy)
			{
				rate1 -= dy;
				lines->py += xinc;
			}
			mlx_pixel_put(data->mlx, data->win, lines->py, lines->px, lines->pc);
			i1++;
		}
	}
}



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

void				start_fdf(t_mlx *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->window, data->window, "FDF");
	move_to_center(data);
	t_map *lines = data->line;
	int i = 1;
	while (lines)
	{
		lines->pc = data->fill;
//		if (lines->flag1 == 1)
		float tempx = lines->px;
		float tempy = lines->py;
			brz1(data, lines, 0, 0);
//		if (lines->flag2 == 1)
			lines->px = tempx;
			lines->py = tempy;
			brz2(data, lines, 0, 0);
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

