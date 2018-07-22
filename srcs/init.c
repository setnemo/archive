/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzamyati <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 19:01:07 by vzamyati          #+#    #+#             */
/*   Updated: 2018/07/21 19:01:09 by vzamyati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		init_data(t_data *data, int i, int x, int y)
{
	if (data->field < 4)
		data->field = 4;
	if (data->field > 10)
		data->field = 10;
	data->colsfield = (COLS - 1) / data->field;
	data->linesfield = (LINES - 1) / data->field;
	while (++i < 100)
		data->random4[i] = 2;
	i = -1;
	while (++i < HOWFOUR)
		data->random4[i] = 4;
	data->core = ft_new_int_matrix(data->field);
	srand(time(NULL));
	x = rand() % data->field;
	y = rand() % data->field;
	data->core[y][x] = data->random4[rand() % 100];
	plus_one(data, x, y);
	data->score = 0;
}

void		init_ncurses(t_data *data)
{
	check_size();
	start_color();
	colors();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	get_field(data, 0);
	get_numbers(data);
}

void		new_game(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < data->field)
	{
		y = -1;
		while (++y < data->field)
			data->core[x][y] = 0;
	}
	srand(time(NULL));
	x = rand() % data->field;
	y = rand() % data->field;
	data->core[y][x] = data->random4[rand() % 100];
	plus_one(data, x, y);
	data->score = 0;
	game_loop(data);
}
