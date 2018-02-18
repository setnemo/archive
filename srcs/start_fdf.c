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
static void			brz2(t_mlx *data, t_map *lines)
{
	const int deltaX = fabsf(lines->px2 - lines->px);
	const int deltaY = fabsf(lines->py2 - lines->py);
	const int signX = lines->px < lines->px2 ? 1 : -1;
	const int signY = lines->py < lines->py2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	mlx_pixel_put(data->mlx, data->win, lines->px2, lines->py2, lines->pc);
	while(lines->px != lines->px2 || lines->py != lines->py2) 
  {
		 mlx_pixel_put(data->mlx, data->win, lines->px, lines->py, lines->pc);
		 const int error2 = error * 2;
		 //
		 if(error2 > -deltaY) 
		 {
			  error -= deltaY;
			  lines->px += signX;
		 }
		 if(error2 < deltaX) 
		 {
			  error += deltaX;
			  lines->py += signY;
		 }
	}
}
static void			brz1(t_mlx *data, t_map *lines)
{
	const int deltaX = fabsf(lines->px1 - lines->px);
	const int deltaY = fabsf(lines->py1 - lines->py);
	const int signX = lines->px < lines->px1 ? 1 : -1;
	const int signY = lines->py < lines->py1 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	mlx_pixel_put(data->mlx, data->win, lines->px1, lines->py1, lines->pc);
	while(lines->px != lines->px1 || lines->py != lines->py1) 
  {
		 mlx_pixel_put(data->mlx, data->win, lines->px, lines->py, lines->pc);
		 const int error2 = error * 2;
		 //
		 if(error2 > -deltaY) 
		 {
			  error -= deltaY;
			  lines->px += signX;
		 }
		 if(error2 < deltaX) 
		 {
			  error += deltaX;
			  lines->py += signY;
		 }
	}
}

static void			move_to_center(t_mlx *data)
{
	float	ratex;
	float	ratey;
	t_map	*lines;

	lines = data->line;
	ratex = (data->window - (data->window / 3)) / data->how_x;
	ratey = (data->window - (data->window / 3)) / data->how_y;
	while (lines)
	{
		lines->px *= 100;
		lines->py *= 100;
		lines->px1 *= 100;
		lines->py1 *= 100;
		lines->px2 *= 100;
		lines->py2 *= 100;
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
			brz1(data, lines);
		if (lines->flag2)
			brz2(data, lines);
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
	mlx_loop(data->mlx);
}

