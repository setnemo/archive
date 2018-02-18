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
static void			for_brz2(int *deltax, int *deltay, t_map *lines)
{
	*deltax = fabsf(lines->px2 - lines->px);
	*deltay = fabsf(lines->py2 - lines->py);
}

static void			brz2(t_mlx *data, t_map *lines, int error, int error2)
{
	int deltax;
	int deltay;
	int signx;
	int signy;

	for_brz2(&deltax, &deltay, lines);
	signx = lines->px < lines->px2 ? 1 : -1;
	signy = lines->py < lines->py2 ? 1 : -1;
	error = deltax - deltay;
	mlx_pixel_put(data->mlx, data->win, lines->px2, lines->py2, lines->pc);
	while(lines->px != lines->px2 || lines->py != lines->py2) 
	{
		mlx_pixel_put(data->mlx, data->win, lines->px, lines->py, lines->pc);
		error2 = error * 2;
		if(error2 > -deltay) 
		{
			error -= deltay;
			lines->px += signx;
		}
		if(error2 < deltax) 
		{
			error += deltax;
			lines->py += signy;
		}
	}
}

static void			for_brz1(int *deltax, int *deltay, t_map *lines)
{
	*deltax = fabsf(lines->px1 - lines->px);
	*deltay = fabsf(lines->py1 - lines->py);
}

static void			brz1(t_mlx *data, t_map *lines, int error, int error2)
{
	int deltax;
	int deltay;
	int signx;
	int signy;

	for_brz1(&deltax, &deltay, lines);
	signx = lines->px < lines->px1 ? 1 : -1;
	signy = lines->py < lines->py1 ? 1 : -1;
	error = deltax - deltay;
	mlx_pixel_put(data->mlx, data->win, lines->px1, lines->py1, lines->pc);
	while(lines->px != lines->px1 || lines->py != lines->py1) 
	{
		mlx_pixel_put(data->mlx, data->win, lines->px, lines->py, lines->pc);
		error2 = error * 2;
		if(error2 > -deltay) 
		{
			error -= deltay;
			lines->px += signx;
		}
		if(error2 < deltax) 
		{
			error += deltax;
			lines->py += signy;
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
	ratex = data->window / data->how_x;
	ratey = data->window / data->how_y;
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
		ft_printf(":ШШШ:lines->px lines->py lines->px1 lines->py1 lines->px2 lines->py2 lines->pz lines->pc\n");
		printf(" %i         %f         %f       %f         %f         %f          %f        %f        %lu\n",i, lines->px, lines->py,lines->px1, lines->py1,lines->px2, lines->py2,lines->pz,lines->pc);
		if (lines->next)
			lines = lines->next;
		else
			break ;
		i++;
	}
	lines = data->line;
	while (lines)
	{
		lines->pc = 0xFFFFFF;
		if (lines->flag1)
			brz1(data, lines, 0, 0);
		if (lines->flag2)
			brz2(data, lines, 0, 0);
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
	mlx_loop(data->mlx);
}

