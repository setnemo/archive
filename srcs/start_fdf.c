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
#define LEG00 "FDF @APAKHOMO"
#define LEG01 "'*' - show legends"
#define LEG02 "COLORIZE"
#define LEG03 "'.' - color"
#define LEG04 "MOVE"
#define LEG05 "'8'  - move up"
#define LEG06 "'2'  - move down"
#define LEG07 "'4'  - move left"
#define LEG08 "'6'  - move right"
#define LEG09 "ZOOM"
#define LEG10 "'+'  ++zoom"
#define LEG11 "'-'  --zoom"
#define LEG12 "ROTATE"
#define LEG13 "'UP'    - move up"
#define LEG14 "'DOWN'  - move down"
#define LEG15 "'LEFT'  - move left"
#define LEG16 "'RIGHT' - move right"
#define LEG17 "RESET"
#define LEG18 "'5'   - reset move"
#define LEG19 "EXIT"
#define LEG20 "'ESC' - exit"

static void			legend(t_mlx *data)
{
	mlx_string_put(data->mlx, data->win, 50, 25, 0x00CC00, LEG00);
	mlx_string_put(data->mlx, data->win, 225, 25, 0x00CC00, LEG01);
	if (data->show == 1)
	{
		mlx_string_put(data->mlx, data->win, 50, 70, 0xfbba00, LEG02);
		mlx_string_put(data->mlx, data->win, 50, 100, 0xff0040, LEG03);
		mlx_string_put(data->mlx, data->win, 225, 70, 0xfbba00, LEG04);
		mlx_string_put(data->mlx, data->win, 225, 100, 0xff0040, LEG05);
		mlx_string_put(data->mlx, data->win, 225, 130, 0xff0040, LEG06);
		mlx_string_put(data->mlx, data->win, 225, 160, 0xff0040, LEG07);
		mlx_string_put(data->mlx, data->win, 225, 190, 0xff0040, LEG08);
		mlx_string_put(data->mlx, data->win, 50, 130, 0xfbba00, LEG09);
		mlx_string_put(data->mlx, data->win, 50, 160, 0xff0040, LEG10);
		mlx_string_put(data->mlx, data->win, 50, 190, 0xff0040, LEG11);
		mlx_string_put(data->mlx, data->win, 425, 70, 0xfbba00, LEG12);
		mlx_string_put(data->mlx, data->win, 425, 100, 0xff0040, LEG13);
		mlx_string_put(data->mlx, data->win, 425, 130, 0xff0040, LEG14);
		mlx_string_put(data->mlx, data->win, 425, 160, 0xff0040, LEG15);
		mlx_string_put(data->mlx, data->win, 425, 190, 0xff0040, LEG16);
		mlx_string_put(data->mlx, data->win, 675, 70, 0xfbba00, LEG17);
		mlx_string_put(data->mlx, data->win, 675, 100, 0xff0040, LEG18);
		mlx_string_put(data->mlx, data->win, 675, 130, 0xfbba00, LEG19);
		mlx_string_put(data->mlx, data->win, 675, 160, 0xff0040, LEG20);
	}
}

static void			shift_fdf(t_mlx *data, int flag)
{
	if (flag == 1)
		data->shiftx += 10;
	if (flag == 2)
		data->shifty += 10;
	if (flag == 3)
		data->shiftx -= 10;
	if (flag == 4)
		data->shifty -= 10;
}

void				move_fdf(t_mlx *data, int flag)
{
	t_map	*lines;

	if (flag != 0)
	{
		shift_fdf(data, flag);
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
	data->shiftx = ((data->window / 2) - ((data->lastx - data->firstx) / 2));
	data->shifty = ((data->window / 2) - ((data->lasty - data->firsty) / 2));
}

void				start_fdf(t_mlx *data)
{
	int		x;
	int		y;
	t_map	*lines;

	lines = data->line;
	y = 0;
	if (data->window > 899)
		legend(data);
	(data->move == 0) ? move_fdf(data, 0) : move_fdf(data, data->move);
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
