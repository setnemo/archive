/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:26:19 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/01 14:26:19 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_pixels(int *coords, int *pixel, t_mlx *data)
{
	float	div;
	int		tmp;

	div = (float)coords[Z] / 7;
	div *= data->height;
	tmp = (int)(div * data->alt);
	pixel[X] = data->x + (data->width * coords[X]) +
	data->width * ((data->point[Y] - 1) - coords[Y]) + data->x_loc;
	pixel[Y] = data->y + (data->height * coords[X]) * data->rot -
	(data->height * ((data->point[Y] - 1) - coords[Y])) * data->rot - tmp - data->y_loc;
	pixel[Z] = coords[Z];
	if (!data->peaks)
		pixel[C] = (coords[C]) ? coords[C] : data->colour;
	else
	pixel[C] = (coords[Z] && data->peaks) ?
	5073779 + ((1 + (1 << 16)) * (coords[Z] * data->alt)) : data->colour;
}

void	soft_line(int p1[4], int p2[4], void *mlx, void *win)
{
	int dx;
	int dy;
	int	p;
	int	neg;
	int	col;

	col = (p1[Z] > p2[Z]) ? p1[C] : p2[C];
	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	dx = ft_abs(p2[X] - p1[X]);
	dy = ft_abs(p2[Y] - p1[Y]);
	p = 2 *dy - dx;
	while (p1[X] < p2[X])
	{
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p1[Y] += neg;
			p = p + 2 * dy - 2 * dx; 
		}
		mlx_pixel_put(mlx, win, p1[X]++, p1[Y], col);
	}	
}

void	sharp_line(int p1[4], int p2[4], void *mlx, void *win)
{
	int dx;
	int dy;
	int	p;
	int	neg;
	int	col;

	col = (p1[Z] > p2[Z]) ? p1[C] : p2[C];
	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	dx = ft_abs(p2[X] - p1[X]);
	dy = ft_abs(p2[Y] - p1[Y]);
	p = 2 *dx - dy;
	while (p1[X] < p2[X])
	{
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p1[X]++;
			p = p + 2 * dx - 2 * dy; 
		}
		mlx_pixel_put(mlx, win, p1[X] - 1, p1[Y], col);
		p1[Y] += neg;
	}	
}

void	draw_line(int p1[4], int p2[4], void *mlx, void *win)
{
	int p1_copy[4];
	int	p2_copy[4];
	int	i;

	i = 0;
	while (i < 4)
	{
		p1_copy[i] = p1[i];
		p2_copy[i] = p2[i];
		i++;
	}
	if ((p2[X] - p1[X] != 0) && ft_abs((p2[Y] - p1[Y]) / (p2[X] - p1[X])) >= 1)
		sharp_line(p1_copy, p2_copy, mlx, win);
	else
		soft_line(p1_copy, p2_copy, mlx, win);
}

void	to_win(t_mlx *data)
{
	int		j;
	int		pixels[data->point[X] * data->point[Y]][4];
	int		d;

	j = -1;
	d = data->point[X] + data->point[Y] - 2;
	while (!((data->height = ceil((data->isize * 2) / 5) / d) * data->zoom))
		d--;
	data->height = ceil(((data->isize * 2) / 5) / d) * data->zoom;
	data->width = ceil(((data->isize * 4) / 5) / d) * data->zoom;
	data->x = (data->isize - (data->width * d)) / 2;
	data->y = ((data->isize - (data->height * d)) * 2) / 3;
	while (++j < data->point[X] * data->point[Y])
		get_pixels(data->loc[j], pixels[j], data);
	while (--j > 0)
	{
		if (j - data->point[X] >= 0) 
			draw_line(pixels[j], pixels[j - data->point[X]], data->mlx, data->win);
		if (j % data->point[X])
			draw_line(pixels[j - 1], pixels[j], data->mlx, data->win);
	}
}
