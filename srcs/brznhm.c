/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brznhm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

static void		soft_line(int p1[3], int p2[3], t_img *img, int color)
{
	int dx;
	int dy;
	int	p;
	int	neg;

	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	dx = ABS(p2[X] - p1[X]);
	dy = ABS(p2[Y] - p1[Y]);
	p = 2 * dy - dx;
	while (p1[X] < p2[X])
	{
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p1[Y] += neg;
			p = p + 2 * dy - 2 * dx;
		}
		img->img_ptr[p1[Y] * img->sl / 4 + p1[X]++] = color;
	}
}

static void		sharp_line(int p1[3], int p2[3], t_img *img, int color)
{
	int dx;
	int dy;
	int	p;
	int	neg;

	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	dx = ABS(p2[X] - p1[X]);
	dy = ABS(p2[Y] - p1[Y]);
	p = 2 * dx - dy;
	while (p1[X] < p2[X])
	{
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p1[X]++;
			p = p + 2 * dx - 2 * dy;
		}
		img->img_ptr[p1[Y] * img->sl / 4 + p1[X] - 1] = color;
		p1[Y] += neg;
	}
}

void			draw_line(int p1[3], int p2[3], t_img *img, int color)
{
	int p1_copy[2];
	int	p2_copy[2];
	int	i;

	i = 0;
	while (i < 2)
	{
		p1_copy[i] = p1[i];
		p2_copy[i] = p2[i];
		i++;
	}
	if ((p2[X] - p1[X] != 0) && ABS((p2[Y] - p1[Y]) / (p2[X] - p1[X])) >= 1)
		sharp_line(p1_copy, p2_copy, img, color);
	else
		soft_line(p1_copy, p2_copy, img, color);
}

