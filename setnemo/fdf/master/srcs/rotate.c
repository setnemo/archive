/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		rotate_x(t_mlx *data, t_map *lines)
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

static void		rotate_y(t_mlx *data, t_map *lines)
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

void			rotate_fdf(t_mlx *data, int l)
{
	t_map *lines;

	lines = data->line;
	if (l == 0)
		rotate_x(data, lines);
	if (l == 1)
		rotate_y(data, lines);
}
