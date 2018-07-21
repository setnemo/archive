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
#include <fcntl.h>

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
	init_pair(17, COLOR_BLACK, COLOR_BLACK);
	init_pair(18, COLOR_WHITE, COLOR_WHITE);
}

void	score2file(t_data *data)
{	
	int		fd;
	char	*sc;

	fd = open("scores.txt", O_WRONLY | O_APPEND);
	if (fd < 0)
	{
		fd = open("scores.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644 | O_APPEND);
		if (fd < 0)
			ft_printf("Error fd open\n");
	}
	sc = ft_itoa(data->score);
	ft_putstr_fd(data->name, fd);
	ft_putstr_fd(" ", fd);
	ft_putendl_fd(sc, fd);
	ft_strdel(&sc);
	close(fd);
}

void		game_over(t_data *data)
{
	int ch;

	score2file(data);
	while (42)
	{
		check_size();
		get_clear();
		timeout(0);
		ch = getch();
		usleep(33333);
		ch == '1' ? new_game(data) : 0;
		ch == '2' ? print_score() : 0;
		// ch = (ch == '3') ? 0 : 0;
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
	system("leaks -quiet game_2048");
	exit(0);
}

void		usage(void)
{
	ft_printf("Usage: ./game_2048 [NICKNAME] [MAP_SIZE]\n");
	exit(0);
}
int			main(int argc, char const *argv[])
{
	t_data	data;
	WINDOW	*win;

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
	win = newwin(COLS,LINES, 0, 0);
	init_ncurses(&data);
	game_loop(&data);
	delwin(win);
	endwin();
	system("leaks -quiet game_2048");
	return (0);
}
