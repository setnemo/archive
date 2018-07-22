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

int			main(int argc, char const *argv[])
{
	t_data	data;

	WINDOW * win;
	if (argc == 1)
		usage();
	ft_bzero(&data, sizeof(t_data));
	if (argc > 1)
		data.name = argv[1];
	if (argc == 3 && argv[2] && ft_atoi(argv[2]) > 3)
		data.field = ft_atoi(argv[2]);
	init_data(&data, -1, 0, 0);
	if (!(initscr()))
	{
		ft_printf("Ncurses problem with memory\n");
		exit(0);
	}
	curs_set(0);
	win = newwin(COLS, LINES, 0, 0);
	init_ncurses(&data);
	greeting(&data);
	delwin(win);
	endwin();
	system("leaks -quiet game_2048");
	return (0);
}
