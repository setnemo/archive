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

void	restart(t_mlx *data)
{
	mlx_clear_window(data->mlx, data->win);
	start_fdf(data);
}

void	colorize(t_mlx *data, int flag)
{
	t_map *lines;

	lines = data->line;
	while (lines)
	{
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

int		deal_key(int k, t_mlx *data)
{
	if (k == 53)
		exit_free(data);
	if (k == 126)
	{
		data->radx += 0.0125;
		rotate_fdf(data, 0);
	}
	if (k == 125)
	{
		data->radx -= 0.0125;
		rotate_fdf(data, 0);
	}
	if (k == 124)
	{
		data->rady += 0.0125;
		rotate_fdf(data, 1);
	}
	if (k == 123)
	{
		data->rady -= 0.0125;
		rotate_fdf(data, 1);
	}
	if (k == 69)
		scale(data, 1);
	if (k == 78)
		scale(data, 2);
	if (k == 91)
		data->move = 4;
	if (k == 84)
		data->move = 2;
	if (k == 86)
		data->move = 3;
	if (k == 88)
		data->move = 1;
	if (k == 8)
	{
		if (data->coloriz == 1)
			data->coloriz = 0;
		else
			data->coloriz = 1;
		colorize(data, data->coloriz);
	}
	if (k == 37)
	{
		if (data->show == 1)
			data->show = 0;
		else
			data->show = 1;
	}
	if (k == 1)
	{
		data->radx = 0;
		data->rady = 0;
		data->move = 0;
	}
	if (k >= 1 && k <= 126)
		restart(data);
	return (k);
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

void			legend(t_mlx *data)
{
	mlx_string_put(data->mlx, data->win, 50, 25, 0x00CC00, "FDF @APAKHOMO");
	mlx_string_put(data->mlx, data->win, 225, 25, 0x00CC00, "L - show legends");
	if (data->show == 1)
	{
		mlx_string_put(data->mlx, data->win, 50, 70, 0xfbba00, "COLORIZE");
		mlx_string_put(data->mlx, data->win, 50, 100, 0xff0040, "'C' - color");
		mlx_string_put(data->mlx, data->win, 225, 70, 0xfbba00, "MOVE");
		mlx_string_put(data->mlx, data->win, 225, 100, 0xff0040, "'8'  - move up");
		mlx_string_put(data->mlx, data->win, 225, 130, 0xff0040, "'2'  - move down");
		mlx_string_put(data->mlx, data->win, 225, 160, 0xff0040, "'4'  - move left");
		mlx_string_put(data->mlx, data->win, 225, 190, 0xff0040, "'6'  - move right");
		mlx_string_put(data->mlx, data->win, 50, 130, 0xfbba00, "ZOOM");
		mlx_string_put(data->mlx, data->win, 50, 160, 0xff0040, "'+'  ++zoom");
		mlx_string_put(data->mlx, data->win, 50, 190, 0xff0040, "'-'  --zoom");
		mlx_string_put(data->mlx, data->win, 425, 70, 0xfbba00, "ROTATE");
		mlx_string_put(data->mlx, data->win, 425, 100, 0xff0040, "'UP'    - move up");
		mlx_string_put(data->mlx, data->win, 425, 130, 0xff0040, "'DOWN'  - move down");
		mlx_string_put(data->mlx, data->win, 425, 160, 0xff0040, "'LEFT'  - move left");
		mlx_string_put(data->mlx, data->win, 425, 190, 0xff0040, "'RIGHT' - move right");
		mlx_string_put(data->mlx, data->win, 675, 70, 0xfbba00, "RESET");
		mlx_string_put(data->mlx, data->win, 675, 100, 0xff0040, "'S'   - reset move");
		mlx_string_put(data->mlx, data->win, 675, 130, 0xfbba00, "EXIT");
		mlx_string_put(data->mlx, data->win, 675, 160, 0xff0040, "'ESC' - exit");
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
	legend(data);
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
