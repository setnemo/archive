/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 13:39:49 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/18 13:39:50 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_global	g_g;
extern t_curs	*g_b;

/*
*** MAKE BORDERS
*/

void	make_border(void)
{
	int y;
	int x;

	y = 0;
	x = 0;
	refresh();
	attron(COLOR_PAIR(18));
	while (y < WIN_HEIGHT - 1)
	{
		mvaddch(y, 0, '@');
		mvaddch(y, 198, '@');
		mvaddch(y, 258, '@');
		y++;
	}
	while (x < WIN_WIDTH - 1)
	{
		mvaddch(0, x, '@');
		mvaddch(WIN_HEIGHT - 1, x, '@');
		x++;
	}
	wrefresh(g_b->win);
}

/*
*** make right side bar
*/

void	make_bar(void)
{
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(Y_BAR_SRT, X_BAR_SRT, "%s", "** PAUSED ** ");
	mvprintw(Y_BAR_SECL, X_BAR_SRT, "%s %d  ", "Cycles/second limit : ",
											g_b->sleep);
	mvprintw(Y_BAR_CYCL, X_BAR_SRT, "%s  %d  ", "Total cycle :",
											g_g.total_cycle);
	mvprintw(Y_BAR_CYCL + 2, X_BAR_SRT, "%s %d  ", "Cycle :       ",
											g_g.total_cycle);
	mvprintw(Y_BAR_PROC, X_BAR_SRT, "%s   %d  ", "Processes : ",
											g_g.num_of_processes);
	show_players();
	mvprintw(g_b->bar_y_st + Y_BAR_CD, X_BAR_SRT, "%s%d ", "CYCLE_TO_DIE : ",
														CYCLE_TO_DIE);
	mvprintw(g_b->bar_y_st + Y_BAR_CDEL, X_BAR_SRT, "%s %d ", "CYCLE_DELTA : ",
														CYCLE_DELTA);
	mvprintw(g_b->bar_y_st + Y_BAR_NL, X_BAR_SRT, "%s %d   ", "NBR_LIVE :    ",
														NBR_LIVE);
	mvprintw(g_b->bar_y_st + Y_BAR_MCH, X_BAR_SRT, "%s  %d ", "MAX_CHECKS : ",
														MAX_CHECKS);
	mvprintw(g_b->bar_y_st + Y_BAR_MCH, X_BAR_SRT, "%s  %d ", "MAX_CHECKS : ",
														MAX_CHECKS);
	add_draw_playerbar();
}

/*
*** initil ncurse liblary
*/

void	print_cursor(void)
{
	if (g_b->pl_nb >= 1)
		draw_new(g_g.players[0].startpos);
	if (g_b->pl_nb >= 2)
		draw_new(g_g.players[1].startpos);
	if (g_b->pl_nb >= 3)
		draw_new(g_g.players[2].startpos);
	if (g_b->pl_nb == 4)
		draw_new(g_g.players[3].startpos);
	wrefresh(g_b->win);
	refresh();
}

void	call_me_baby_i_am_alive(int index)
{
	g_b->live[index] = g_g.total_cycle + 1;
}

/*
*** redraw bar every cycle to show change
*/

void	redraw_bar(void)
{
	refresh();
	attron(COLOR_PAIR(15) | A_BOLD);
	mvprintw(Y_BAR_SECL, X_BAR_SRT + 23, "%d   ", g_b->sleep);
	mvprintw(Y_BAR_CYCL, X_BAR_SRT + 14, " %d    ", g_g.total_cycle);
	mvprintw(Y_BAR_CYCL + 2, X_BAR_SRT + 14, " %d   ", g_g.cycle);
	redraw_player_bar();
	mvprintw(Y_BAR_PROC, X_BAR_SRT + 15, "%d    ", g_g.num_of_processes);
	mvprintw(g_b->bar_y_st + Y_BAR_CD, X_BAR_SRT + 15, "%d    ",
				g_g.cycle_to_die);
	mvprintw(g_b->bar_y_st + Y_BAR_CDEL, X_BAR_SRT + 15, "%d    "
			, CYCLE_DELTA);
	mvprintw(g_b->bar_y_st + Y_BAR_NL, X_BAR_SRT + 15, "%d    ",
			NBR_LIVE);
	mvprintw(g_b->bar_y_st + Y_BAR_MCH, X_BAR_SRT + 14, " %d   ",
			MAX_CHECKS - g_g.checks);
	wrefresh(g_b->win);
}
