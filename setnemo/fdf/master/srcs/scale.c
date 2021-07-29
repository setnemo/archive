/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		scale0(t_mlx *data, t_map *lines)
{
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

static void		scale1(t_mlx *data, t_map *lines)
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
}

static void		scale2(t_mlx *data, t_map *lines)
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
}

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
		scale1(data, lines);
		return ;
	}
	if (flag == 2)
	{
		scale2(data, lines);
		return ;
	}
	scale0(data, lines);
}
