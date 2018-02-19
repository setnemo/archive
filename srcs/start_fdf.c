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

static void			brz2(t_mlx *data, t_map *lines, int error, int error2)
{
	if (error2 | error)
		;
	int xi = lines->py;
	int yi = lines->px;
	int xf = lines->py2;
	int yf = lines->px2;
	int dx;
	int dy;
	int i;
	int xinc;
	int yinc;
	int cumul;
	int x;
	int y;

	x = xi;
	y = yi;
	dx = xf - xi;
	dy = yf - yi;
	xinc = ( dx > 0 ) ? 1 : -1;
	yinc = ( dy > 0 ) ? 1 : -1;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
	mlx_pixel_put(data->mlx, data->win, x, y, lines->pc);
	if ( dx > dy )
	{
		cumul = (dx / 2);
		i = 1;
		while (i <= dx)
		{
			x += xinc;
			cumul += dy;
			i++;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			mlx_pixel_put(data->mlx, data->win, x, y, lines->pc);
		}
	}
	else
	{
		cumul = dy / 2;
		i = 1;
		while (i <= dy)
		{
			y += yinc ;
			cumul += dx;
			if ( cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			mlx_pixel_put(data->mlx, data->win, x, y, lines->pc);
			i++;
		}
	}
}


static void			brz1(t_mlx *data, t_map *lines, int error, int error2)
{
	if (error2 | error)
		;
	int xi = lines->py;
	int yi = lines->px;
	int xf = lines->py1;
	int yf = lines->px1;
	int dx;
	int dy;
	int i;
	int xinc;
	int yinc;
	int cumul;
	int x;
	int y;

	x = xi;
	y = yi;
	dx = xf - xi;
	dy = yf - yi;
	xinc = ( dx > 0 ) ? 1 : -1;
	yinc = ( dy > 0 ) ? 1 : -1;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
	mlx_pixel_put(data->mlx, data->win, x, y, lines->pc);
	if ( dx > dy )
	{
		cumul = (dx / 2);
		i = 1;
		while (i <= dx)
		{
			x += xinc;
			cumul += dy;
			i++;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			mlx_pixel_put(data->mlx, data->win, x, y, lines->pc);
		}
	}
	else
	{
		cumul = dy / 2;
		i = 1;
		while (i <= dy)
		{
			y += yinc ;
			cumul += dx;
			if ( cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			mlx_pixel_put(data->mlx, data->win, x, y, lines->pc);
			i++;
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
			brz1(data, lines, 0, 0);
//		if (lines->flag2 == 1)
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

