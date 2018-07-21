/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 10:23:57 by apakhomo          #+#    #+#             */
/*   Updated: 2018/07/21 10:24:04 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"


void	colors(void)
{
	init_color(COLOR_WHITE, 300, 300, 300);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(21, COLOR_BLACK, COLOR_GREEN);
	init_pair(31, COLOR_WHITE, COLOR_GREEN);
	init_pair(22, COLOR_BLACK, COLOR_RED);
	init_pair(32, COLOR_WHITE, COLOR_RED);
	init_pair(23, COLOR_BLACK, COLOR_YELLOW);
	init_pair(33, COLOR_WHITE, COLOR_YELLOW);
	init_pair(24, COLOR_BLACK, COLOR_BLUE);
	init_pair(34, COLOR_WHITE, COLOR_BLUE);
	init_pair(14, COLOR_WHITE, COLOR_BLACK);
	init_pair(41, COLOR_BLACK, COLOR_WHITE);
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
	init_pair(17, COLOR_BLACK, COLOR_BLACK); //затирать
	init_pair(18, COLOR_WHITE, COLOR_WHITE);
}

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

int			main(int argc, char const *argv[])
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	if (argv[1] && ft_atoi(argv[1]) > 3)
		data.field = ft_atoi(argv[1]);
	init_data(&data, -1, 0, 0);
	/* NCURSES START */

	if (!(initscr()))
		ft_printf("Ncurses problem with memory\n");

	curs_set(0);
	WINDOW *win;
	win = newwin(COLS,LINES, 0, 0);
	init_ncurses(&data);
	game_loop(&data);
	delwin(win);
	endwin();
	system("leaks -quiet game_2048");
	return (0);
}










