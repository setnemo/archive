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

static int	ncureses_and_game(t_data *data)
{
	WINDOW * win;
	curs_set(0);
	win = newwin(COLS, LINES, 0, 0);
	init_ncurses(data);
	greeting(data);
	delwin(win);
	endwin();
	return (0);
}

int			main(int argc, char const *argv[])
{
	t_data	data;

	if (argc == 1)
		usage();
	ft_bzero(&data, sizeof(t_data));
	if (argc > 1)
		data.name = argv[1];
	if (argc > 2 && argv[2] && ft_atoi(argv[2]) > 3)
		data.field = ft_atoi(argv[2]);
	if (argc > 3 && argv[3] && ft_atoi(argv[3]) > -1 && ft_atoi(argv[3]) < 101)
		data.howfour = ft_atoi(argv[3]);
	else
		data.howfour = 20;
	init_data(&data, -1, 0, 0);
	if (!(initscr()))
	{
		ft_printf("Ncurses problem with memory\n");
		exit(0);
	}
	return (ncureses_and_game(&data));
}
