/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_curse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:36:10 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/26 14:36:11 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_global	g_g;
extern t_curs	*g_b;

/*
*** START_COLORS
*/

void	colors(void)
{
	init_color(COLOR_WHITE, 300, 300, 300);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(21, COLOR_BLACK, COLOR_GREEN);
	init_pair(31, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(22, COLOR_BLACK, COLOR_RED);
	init_pair(32, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(23, COLOR_BLACK, COLOR_YELLOW);
	init_pair(33, COLOR_WHITE, COLOR_YELLOW);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(24, COLOR_BLACK, COLOR_BLUE);
	init_pair(34, COLOR_WHITE, COLOR_BLUE);
	init_pair(14, COLOR_WHITE, COLOR_BLACK);
	init_pair(41, COLOR_BLACK, COLOR_WHITE);
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
	init_pair(17, COLOR_BLACK, COLOR_BLACK);
	init_pair(18, COLOR_WHITE, COLOR_WHITE);
}

void	init_curs(void)
{
	g_b->pl_nb = g_g.num_of_players;
	if (!(initscr()))
		ft_er_init();
	ft_check_size_win();
	start_color();
	keypad(stdscr, TRUE);
	nodelay(g_b->win, FALSE);
	g_b->win = newwin(WIN_HEIGHT - 4, 194, 3, 3);
	colors();
	curs_set(0);
	bkgd(COLOR_PAIR(17));
	signal(SIGINT, siginthandler);
	make_border();
	print_map();
	wattron(g_b->win, COLOR_PAIR(14));
	make_bar();
	print_cursor();
	if (g_b->music == 1 && g_b->treck == 1)
		start_music();
	refresh();
	wrefresh(g_b->win);
}

/*
*** first draw map
*/

void	curse(void)
{
	init_curs();
	noecho();
	while (g_b->key != 32)
	{
		g_b->key = getch();
		hotkey();
	}
	g_b->pause = (g_b->pause == 0 ? 1 : 0);
	mvprintw(Y_BAR_SRT, X_BAR_SRT, "%s", g_b->pause == 0 ?
			"** PAUSED ** " : "** RUNNING **");
}
