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

	i = -1;
	// while (++i < data->field)
	// {
	// 	j = data->field
	// 	while (++j < data->field)
	// 	{
			
	// 	}
	// }
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