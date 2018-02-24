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

// void	z(t_mlx *data, int flag)
// {
// 	t_map *lines;

// 	lines = data->line;
// 	while (lines)
// 	{
// 		lines->pz = (flag == 0) ? (lines->pz += 1) : (lines->pz -= 1);
// 		printf("test->pz:%f\n", lines->pz);
// 		if (lines->next)
// 			lines = lines->next;
// 		else
// 			break ;
// 	}
// 	rotate_fdf(data, 3);
// }

void	colorize(t_mlx *data, int flag)
{
	t_map *lines;

	lines = data->line;
	while (lines)
	{
		printf("flag:%i\n", flag);
		if (flag == 1)
		{
			if (lines->z > 0)
				lines->pc = 0xCC0000;
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

void	exit_free(t_mlx *data)
{
	free_data(data, 0);
	system("leaks -quiet fdf");
	exit(0);
}

// int		deal_key(int k, t_mlx *data)
// {
// 	if (k == 65307)
// 		exit_free(data);
// 	if (k == 122)
// 	{
// 		data->radx += 0.017452;
// 		rotate_fdf(data, 0);
// 	}
// 	if (k == 120)
// 	{
// 		data->radx -= 0.017452;
// 		rotate_fdf(data, 0);
// 	}
// 	if (k == 99)
// 	{
// 		data->rady += 0.017452;
// 		rotate_fdf(data, 1);
// 	}
// 	if (k == 118)
// 	{
// 		data->rady -= 0.017452;
// 		rotate_fdf(data, 1);
// 	}
// 	if (k == 98)
// 	{
// 		data->radz += 0.017452;
// 		rotate_fdf(data, 2);
// 	}
// 	if (k == 110)
// 	{
// 		data->radz -= 0.017452;
// 		rotate_fdf(data, 2);
// 	}
// 	ft_testintstr(k, "key");
// 	if (k == 53 || (k >= 99 && k <= 126) )
// 		restart(data);
// 	return (k);
// }

int		deal_key(int k, t_mlx *data)
{
	if (k == 53)
		exit_free(data);
	if (k == 123)
	{
		data->radx += 0.0125;
		rotate_fdf(data, 0);
	}
	if (k == 124)
	{
		data->radx -= 0.0125;
		rotate_fdf(data, 0);
	}
	if (k == 125)
	{
		data->rady += 0.0125;
		rotate_fdf(data, 1);
	}
	if (k == 126)
	{
		data->rady -= 0.0125;
		rotate_fdf(data, 1);
	}
	if (k == 43)
	{
		data->radz += 0.0125;
		rotate_fdf(data, 2);
	}
	if (k == 47)
	{
		data->radz -= 0.0125;
		rotate_fdf(data, 2);
	}
	if (k == 24)
		scale(data, 1);
	if (k == 27)
		scale(data, 2);
	if (k == 91)
		data->move = 4;
	if (k == 84)
		data->move = 2;
	if (k == 86)
		data->move = 3;
	if (k == 88)
		data->move = 1;
	// if (k == 6)
	// 	z(data, 0);
	// if (k == 7)
	// 	z(data, 1);
	if (k == 8)
	{
		if (data->coloriz == 1)
			data->coloriz = 0;
		else
			data->coloriz = 1;
		colorize(data, data->coloriz);
	}
	// if (k == 25)
	// 	z(data, 1);

	ft_testintstr(k, "key");
	if (k >= 6 && k <= 126)
		restart(data);
	return (k);
}

// int		deal_key(int k, t_mlx *data)
// {
// 	if (k == 53)
// 		exit_free(data);
// 	if (k == 123)
// 	{
// 		data->radx += 0.08;
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

void			scale(t_mlx *data, int flag)
{
	t_map	*lines;

	if (flag == 0)
		data->zoom = (data->window / 2) / data->how_x;
	lines = data->line;
	data->firstx = data->line->px;
	data->firsty = data->line->py;
	if (flag == 1)
	{
		while (lines)
		{
			data->lastx = lines->px;
			data->lasty = lines->py;
			lines->px *= 1.05;
			lines->py *= 1.05;
			if (lines->next)
				lines = lines->next;
			else
				break ;
		}
		return ;
	}
	if (flag == 2)
	{
		while (lines)
		{
			data->lastx = lines->px;
			data->lasty = lines->py;
			lines->px *= 0.95;
			lines->py *= 0.95;
			if (lines->next)
				lines = lines->next;
			else
				break ;
		}
		return ;
	}
	while (lines)
	{
		lines->z = lines->pz;
		data->lastx = lines->px;
		data->lasty = lines->py;
		lines->px *= data->zoom;
		lines->py *= data->zoom;
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
}

void				move_fdf(t_mlx *data, int flag)
{
	t_map	*lines;

	if (flag != 0)
	{
		if (flag == 1)
			data->shiftx += 10;
		if (flag == 2)
			data->shifty += 10;
		if (flag == 3)
			data->shiftx -= 10;
		if (flag == 4)
			data->shifty -= 10;
		return ;
	}
	lines = data->line;
	data->firstx = data->line->px;
	data->firsty = data->line->py;
	while (lines)
	{
		data->lastx = lines->px;
		data->lasty = lines->py;
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
	lines = data->line;
	data->shiftx = ((data->window / 2) - ((data->lastx - data->firstx)/2));
	data->shifty = ((data->window / 2) - ((data->lasty - data->firsty)/2));
}

void				start_fdf(t_mlx *data)
{
	int x;
	int y;
	t_map *lines;

	lines = data->line;
	x = 0;
	y = 0;
	if (data->move == 0)
		move_fdf(data, 0);
	else
		move_fdf(data, data->move);
	while (y < data->how_y)
	{
		x = 0;
		while (x < data->how_x)
		{
			brz_start(data, lines, y, x);
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
//		printf(" %i         %f %f %f %d         %f       %f         %f         %f          %f        %f        %lu\n",i, lines->px, lines->py,lines->px1, lines->py1,lines->px2, lines->py2,lines->pz,lines->pc);
		//i++;
