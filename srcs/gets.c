/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:01:00 by apakhomo          #+#    #+#             */
/*   Updated: 2018/07/21 15:01:06 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		get_clear(void)
{
	int i;
	int j;

	i = -1;
	attron(COLOR_PAIR(17));
	while (++i < COLS)
	{
		j = -1;
		while (++j < LINES)
		{
			mvprintw(j, i, " ");
		}
	}
}

void		get_numbers(t_data *data)
{
	int i;
	int j;
	char *temp;

	i = -1;
	attron(COLOR_PAIR(1));
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			temp = ft_itoa(data->core[i][j]);
			mvprintw(data->linesfield / 2 + i * data->linesfield,
				data->colsfield / 2 + j * data->colsfield, temp);
			ft_strdel(&temp);
		}
	}
}

void		get_field(t_data *data, int i)
{
	int j;

	i = -1;
	attron(COLOR_PAIR(15));
	data->colsfield = (COLS - 1) / data->field;
	data->linesfield = (LINES - 1) / data->field;
	while (++i < data->colsfield * data->field + 1)
	{
		j = 0;
		while (j < data->linesfield * data->field + 1)
		{
			if (i % data->colsfield == 0)
			{
				if (j % data->linesfield == 0)
					mvprintw(j, i, "+");
				else
					mvprintw(j, i, "|");
			}
			else if (j % data->linesfield == 0)
				mvprintw(j, i, "-");
			else
				mvprintw(j, i, " ");
			j++;
		}
	}
}

