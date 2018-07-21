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

	i = -1;
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			if (i - 1 > -1 && data->core[i][j] == data->core[i - 1][j])
			{
				data->core[i][j] *= 2;
				data->core[i - 1][j] = 0;
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
			}
		}
	}
}
