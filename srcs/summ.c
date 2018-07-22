/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   summ.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 17:51:45 by apakhomo          #+#    #+#             */
/*   Updated: 2018/07/21 17:51:48 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		sum_numbers_down(t_data *data)
{
	int i;
	int j;

	i = data->field;
	while (--i > -1)
	{
		j = -1;
		while (++j < data->field)
		{
			if (i - 1 > -1 && data->core[i][j] == data->core[i - 1][j])
			{
				data->core[i][j] *= 2;
				data->core[i - 1][j] = 0;
				data->score += data->core[i][j];
			}
		}
	}
}

void		sum_numbers_left(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			if (j + 1 < data->field && data->core[i][j] == data->core[i][j + 1])
			{
				data->core[i][j] *= 2;
				data->core[i][j + 1] = 0;
				data->score += data->core[i][j];
			}
		}
	}
}

void		plus_one(t_data *data, int x, int y)
{
	int all;
	int i;
	int j;

	all = 0;
	i = -1;
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			if (data->core[i][j] == 0)
				all++;
		}
	}
	if (all == 0)
		game_over(data);
	x = rand() % data->field;
	y = rand() % data->field;
	while (data->core[y][x] != 0)
	{
		x = rand() % data->field;
		y = rand() % data->field;
	}
	data->core[y][x] = data->random4[rand() % 100];
}
