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
			get_color(data, i, j);
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

void		get_color(t_data *data, int i, int j)
{
	if (data->core[i][j] == 2)
		attron(COLOR_PAIR(2));
	else if (data->core[i][j] == 4)
		attron(COLOR_PAIR(3));
	else if (data->core[i][j] == 8)
		attron(COLOR_PAIR(4));
	else if (data->core[i][j] == 16)
		attron(COLOR_PAIR(21));
	else if (data->core[i][j] == 32)
		attron(COLOR_PAIR(31));
	else if (data->core[i][j] == 64)
		attron(COLOR_PAIR(22));
	else if (data->core[i][j] == 128)
		attron(COLOR_PAIR(32));
	else if (data->core[i][j] == 256)
		attron(COLOR_PAIR(23));
	else if (data->core[i][j] == 512)
		attron(COLOR_PAIR(33));
	else if (data->core[i][j] == 1024)
		attron(COLOR_PAIR(24));
	else if (data->core[i][j] == 2048)
		attron(COLOR_PAIR(34));
	else
		attron(COLOR_PAIR(1));
}

