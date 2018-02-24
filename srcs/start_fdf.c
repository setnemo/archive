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
		data->radx += 0.025;
		rotate_fdf(data, 0);
	}
	if (k == 124)
	{
		data->radx -= 0.025;
		rotate_fdf(data, 0);
	}
	if (k == 125)
	{
		data->rady += 0.025;
		rotate_fdf(data, 1);
	}
	if (k == 126)
	{
		data->rady -= 0.025;
		rotate_fdf(data, 1);
	}
	if (k == 43)
	{
		data->radz += 0.025;
		rotate_fdf(data, 2);
	}
	if (k == 47)
	{
		data->radz -= 0.025;
		rotate_fdf(data, 2);
	}
	ft_testintstr(k, "key");
	if (k >= 43 && k <= 126)
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

void			scale(t_mlx *data)
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
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
}

void				move_fdf(t_mlx *data)
{
	t_map	*lines;

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
	// while (lines)
	// {
	// 	lines->px += data->shiftx;
	// 	lines->py += data->shifty;
	// 	if (lines->next)
	// 		lines = lines->next;
	// 	else
	// 		break ;
	// }
}

void				start_fdf(t_mlx *data)
{
	int x;
	int y;
	t_map *lines;

	lines = data->line;
	x = 0;
	y = 0;
	move_fdf(data);
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
