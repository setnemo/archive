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

void		mv_numbers_down(t_data *data, int *count)
{
	int i;
	int j;

	i = -1;
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			if (data->core[i][j] == 0 && i - 1 > -1)
			{
				data->core[i][j] = data->core[i - 1][j];
				data->core[i - 1][j] = 0;
			}
		}
	}
	*count += 1;
}

void		mv_numbers_up(t_data *data, int *count)
{
	int i;
	int j;

	i = -1;
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			if (data->core[i][j] == 0 && i + 1 < data->field)
			{
				data->core[i][j] = data->core[i + 1][j];
				data->core[i + 1][j] = 0;
			}
		}
	}
	*count += 1;
}

void		mv_numbers_left(t_data *data, int *count)
{
	int i;
	int j;

	i = -1;
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			if (data->core[i][j] == 0 && j + 1 < data->field)
			{
				data->core[i][j] = data->core[i][j + 1];
				data->core[i][j + 1] = 0;
			}
		}
	}
	*count += 1;
}

void		mv_numbers_right(t_data *data, int *count)
{
	int i;
	int j;

	i = -1;
	while (++i < data->field)
	{
		j = data->field;
		while (--j > -1)
		{
			if (data->core[i][j] == 0 && j - 1 > -1)
			{
				data->core[i][j] = data->core[i][j - 1];
				data->core[i][j - 1] = 0;
			}
		}
	}
	*count += 1;
}

