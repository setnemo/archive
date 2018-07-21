/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:10:00 by apakhomo          #+#    #+#             */
/*   Updated: 2018/07/21 15:10:02 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		plus_one(t_data *data, int x, int y)
{
	x = rand() % data->field;
	y = rand() % data->field;
	while (data->core[y][x] != 0)
	{
		x = rand() % data->field;
		y = rand() % data->field;
	}
	data->core[y][x] = data->random4[rand() % 100];
}

void		mv_numbers_down(t_data *data)
{
	int i;
	int j;
	int count;

	j = -1;
	count = 0;
	while (++j < data->field)
	{
		i = data->field;
		while (--i > -1)
		{
			mvprintw(i, j, "æ");
			if (data->core[j][i] == 0 && i - 1 > -1 && data->core[j][i - 1] != 0 && ++count)
			{
				data->core[j][i] = data->core[j][i - 1];
			}
		}
	}
}

void		mv_numbers_up(t_data *data)
{
	;
}

void		mv_numbers_left(t_data *data)
{
	;
}

void		mv_numbers_right(t_data *data)
{
	;
}