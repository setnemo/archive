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
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
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

void		game_over(void)
{
	endwin();
	system("leaks -quiet game_2048");
	exit(0);
}

int			main(int argc, char const *argv[])
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	if (argc > 1 && argv[1] && ft_atoi(argv[1]) > 3)
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
