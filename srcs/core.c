/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"


static void	increment_neighbor(int y, int x, t_data *data)
{
	if (y - 1 >= 0)
	{
		if (data->field[y - 1][x] != -1)
			data->field[y - 1][x]++;
		if (x + 1 < data->img->how_x && data->field[y - 1][x + 1] != -1)
			data->field[y - 1][x + 1]++;
		if (x - 1 >= 0 && data->field[y - 1][x - 1] != -1)
			data->field[y - 1][x - 1]++;
	}
	if (y + 1 < data->img->how_y)
	{
		if (data->field[y + 1][x] != -1)
			data->field[y + 1][x]++;
		if (x + 1 < data->img->how_x && data->field[y + 1][x + 1] != -1)
			data->field[y + 1][x + 1]++;
		if (x - 1 >= 0 && data->field[y + 1][x - 1] != -1)
			data->field[y + 1][x - 1]++;
	}
	if (x - 1 >= 0 && data->field[y][x - 1] != -1)
		data->field[y][x - 1]++;
	if (x + 1 < data->img->how_x && data->field[y][x + 1] != -1)
		data->field[y][x + 1]++;
}

void		solve_distance(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->img->how_y)
	{
		j = -1;
		while (++j < data->img->how_x)
		{
			if (data->field[i][j] == -1)
			{
				ft_printf("i:%i j:%i check:%i\n", i, j);
				increment_neighbor(i, j, data);
			}
		}
	}
}
