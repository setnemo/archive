/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotkey.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:54:23 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/26 14:54:27 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"
#include <fcntl.h>

extern t_global	g_g;
extern t_curs	*g_b;

/*
*** redraw player bar
*/

void	redraw_player_bar(void)
{
	if (g_b->pl_nb >= 1)
	{
		mvprintw(Y_BAR_PL1LL, X_BAR_SCL + 26, "%d  ", g_b->live[0]);
		mvprintw(Y_BAR_PL1LIC, X_BAR_SCL + 26, "%d    ", g_g.live[0]);
	}
	if (g_b->pl_nb >= 2)
	{
		mvprintw(Y_BAR_PL2LL, X_BAR_SCL + 26, "%d   ", g_b->live[1]);
		mvprintw(Y_BAR_PL2LIC, X_BAR_SCL + 26, "%d    ", g_g.live[1]);
	}
	if (g_b->pl_nb >= 3)
	{
		mvprintw(Y_BAR_PL3LL, X_BAR_SCL + 26, "%d   ", g_b->live[2]);
		mvprintw(Y_BAR_PL3LIC, X_BAR_SCL + 26, "%d    ", g_g.live[2]);
	}
	if (g_b->pl_nb == 4)
	{
		mvprintw(Y_BAR_PL4LL, X_BAR_SCL + 26, "%d    ", g_b->live[3]);
		mvprintw(Y_BAR_PL4LIC, X_BAR_SCL + 26, "%d     ", g_g.live[3]);
	}
}

/*
*** hotkey
*/

void	hotkey(void)
{
	if (g_b->key == 27)
		exit_curse();
	if (g_b->key == KEY_LEFT && g_b->sleep > 5)
		g_b->sleep -= 5;
	if (g_b->key == KEY_RIGHT && g_b->sleep < 500)
		g_b->sleep += 5;
	if (g_b->key == KEY_DOWN)
		stop_music();
	if (g_b->key == KEY_UP)
		change_treck();
	redraw_bar();
}

/*
*** pause
*/

void	pause_key(void)
{
	g_b->pause = (g_b->pause == 0 ? 1 : 0);
	mvprintw(Y_BAR_SRT, X_BAR_SRT, "%s", g_b->pause == 0 ?
			"** PAUSED ** " : "** RUNNING **");
	g_b->key = 0;
	while (g_b->key != 32)
	{
		g_b->key = getch();
		hotkey();
	}
	g_b->pause = (g_b->pause == 0 ? 1 : 0);
	mvprintw(Y_BAR_SRT, X_BAR_SRT, "%s", g_b->pause == 0 ?
			"** PAUSED ** " : "** RUNNING **");
}

/*
*** Call from main
*/

void	readkey(void)
{
	if (g_g.kill == 1)
	{
		system("kill -SIGSTOP $(pgrep afplay) > /dev/null 2>&1");
		system("afplay mp3/fire.mp3 & > /dev/null 2>&1");
		system("kill -SIGSTP $(pgrep afplay) > /dev/null 2>&1");
	}
	timeout(1000 / g_b->sleep);
	halfdelay(0);
	g_b->key = getch();
	hotkey();
	if (g_b->key == 32)
		pause_key();
	g_b->key = 0;
}

/*
*** Handle Ctrl-C
*/

void	siginthandler(int param)
{
	if (param > 0)
		system("kill $(pgrep afplay) > /dev/null 2>&1");
	system("kill $(pgrep afplay) > /dev/null 2>&1");
	delwin(g_b->win);
	endwin();
	free(g_b->map);
	free(g_b->live);
	free(g_b);
	printf("Stupid user pressed Ctrl+C\n");
	exit(1);
}
