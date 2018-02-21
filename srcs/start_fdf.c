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

void	restart(t_mlx *data)
{
	mlx_clear_window(data->mlx, data->win);
	start_fdf(data);
}

void	exit_free(t_mlx *data)
{
	free_data(data, 0);
	system("leaks -quiet fdf");
	exit(0);
}

void		rotate_x(t_mlx *data, t_map *lines)
{
	float x;
	float y;
	float z;
	while (lines)
	{
	x = lines->px;
	y = lines->py;
	z = lines->pz;
	lines->px = x * 1 + y * 0 + z * 0;
	lines->py = x * 0 + y * cos(data->radx) - z * sin(data->radx);
	lines->pz = x * 0 + y * sin(data->radx) + z * cos(data->radx);
	if (lines->next)
			lines = lines->next;
		else
			break ;		
	}
}
void		rotate_y(t_mlx *data, t_map *lines)
{
	float x;
	float y;
	float z;
	while (lines)
	{
	x = lines->px;
	y = lines->py;
	z = lines->pz;
	lines->px = x * cos(data->rady) + y * 0 + z * sin(data->rady);
	lines->py = x * 0 + y * 1 + z * 0;
	lines->pz = x * -sin(data->rady) + y * 0 + z * cos(data->rady);
	if (lines->next)
			lines = lines->next;
		else
			break ;		
	}
}
void		rotate_z(t_mlx *data, t_map *lines)
{
	float x;
	float y;
	float z;

	while (lines)
	{
		x = lines->px;
		y = lines->py;
		z = lines->pz;
		lines->px = x * cos(data->radz) + y * -sin(data->radz) + z * 0;
		lines->py = x * sin(data->radz) + y * cos(data->radz) + z * 0;
		lines->pz = x * 0 + y * 0 + z * 1;
		if (lines->next)
			lines = lines->next;
		else
			break ;		
	}
}

void		rotate_fdf(t_mlx *data, int l)
{
	t_map *lines;

	lines = data->line;
	if (l == 0)
		rotate_x(data, lines);
	if (l == 1)
		rotate_y(data, lines);
	if (l == 2)
		rotate_z(data, lines);
}

int		deal_key(int k, t_mlx *data)
{
	if (k == 65307)
		exit_free(data);
	if (k == 122)
	{
		data->radx += 0.017452;
		rotate_fdf(data, 0);
	}
	if (k == 120)
	{
		data->radx -= 0.017452;
		rotate_fdf(data, 0);
	}
	if (k == 99)
	{
		data->rady += 0.017452;
		rotate_fdf(data, 1);
	}
	if (k == 118)
	{
		data->rady -= 0.017452;
		rotate_fdf(data, 1);
	}
	if (k == 98)
	{
		data->radz += 0.017452;
		rotate_fdf(data, 2);
	}
	if (k == 110)
	{
		data->radz -= 0.017452;
		rotate_fdf(data, 2);
	}
	ft_testintstr(k, "key");
	if (k == 53 || (k >= 99 && k <= 126) )
		restart(data);
	return (k);
}

// int		deal_key(int k, t_mlx *data)
// {
// 	if (k == 53)
// 		exit_free(data);
// 	if (k == 123)
// 	{
// 		data->radx += 0.017452;
// 		rotate_fdf(data, 0, 0);
// 	}
// 	if (k == 124)
// 	{
// 		data->radx -= 0.017452;
// 		rotate_fdf(data, 0, 1);
// 	}
// 	if (k == 125)
// 	{
// 		data->rady += 0.017452;
// 		rotate_fdf(data, 1, 0);
// 	}
// 	if (k == 126)
// 	{
// 		data->rady -= 0.017452;
// 		rotate_fdf(data, 1, 1);
// 	}
// 	if (k == 83)
// 	{
// 		data->radz -= 0.017452;
// 		rotate_fdf(data, 2, 0);
// 	}
// 	if (k == 85)
// 	{
// 		data->radz -= 0.017452;
// 		rotate_fdf(data, 2, 1);
// 	}
// 	ft_testintstr(k, "key");
// 	if (k == 53 || (k >= 123 && k <= 126) || k == 83 || k == 85)
// 		restart(data);
// 	return (k);
// }

void			move_to_center(t_mlx *data)
{
	float	ratex;
	t_map	*lines;

	ratex = (data->window / 2) / data->how_x;
	lines = data->line;
	data->firstx = data->line->px;
	data->firsty = data->line->py;
	while (lines)
	{
		data->lastx = lines->px;
		data->lasty = lines->py;
		lines->px *= ratex;
		lines->py *= ratex;
		lines->px1 *= ratex;
		lines->py1 *= ratex;
		lines->px2 *= ratex;
		lines->py2 *= ratex;
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
	lines = data->line;
	float ratey;
	ratex = ((data->window / 2) - ((data->lastx - data->firstx)/2))/2;
	ratey = ((data->window / 2) - ((data->lasty - data->firsty)/2))/2;
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
		if ( rate >= brz->dy)
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
	int i = 0;
	while (i < how)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}

static void			brz_core(t_mlx *data, t_map	*lines, int flag)
{
	t_brz		brz1;
	t_map		*temp;

	temp = lines;
	brz1.py = lines->py;
	brz1.px = lines->px;
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
	brz1.yinc = (brz1.dy > 0 ) ? 1 : -1;
	brz1.dx = abs(brz1.dx); 
	brz1.dy = abs(brz1.dy);
	brz1.pc = (lines->pc == 0) ? data->fill : lines->pc;
	brz1.dx > brz1.dy ? brzh1(data, &brz1, 0, 0) : brzh2(data, &brz1, 0, 0);
}

static void			brz_start(t_mlx *data, t_map *lines, int y, int x)
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

void				start_fdf(t_mlx *data)
{

	t_map *lines = data->line;

	int x = 0;
	int y = 0;
	while (y < data->how_y)
	{
		x = 0;
		while (x < data->how_x)
		{
			brz_start(data, lines, y, x);
			printf("y:%i x:%i\n",y, x);
			if (lines->next)
				lines = lines->next;
			else
				break ;
			x++;
		}
		y++;
	}
}

		// else
		// 	y = 0;
	//	printf(":ШШШ:lines->px lines->py lines->px1 lines->py1 lines->px2 lines->py2 lines->pz lines->pc\n");
		//printf("%f		%f		%f		%f		%f		%f\n",lines->px, lines->py,lines->px1, lines->py1,lines->px2, lines->py2);
//		printf(" %i         %f         %f       %f         %f         %f          %f        %f        %lu\n",i, lines->px, lines->py,lines->px1, lines->py1,lines->px2, lines->py2,lines->pz,lines->pc);
		//i++;
