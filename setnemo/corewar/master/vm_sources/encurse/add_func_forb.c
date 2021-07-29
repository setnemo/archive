/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func_forb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:36:17 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/05/01 13:36:19 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_curs	*g_b;

/*
*** on/off music
*/

void	stop_music(void)
{
	g_b->music = g_b->music == 1 ? 0 : 1;
	if (!g_b->music)
	{
		system("kill $(pgrep afplay) > /dev/null 2>&1");
		attron(COLOR_PAIR(2));
		mvprintw(g_b->bar_y_st + Y_KEY_DOWN, X_BAR_SRT + 19, "%s ", "OFF ");
	}
	else if (g_b->music)
	{
		attron(COLOR_PAIR(1));
		mvprintw(g_b->bar_y_st + Y_KEY_DOWN, X_BAR_SRT + 19, "%s ", "ON  ");
	}
}

/*
*** change treck
*/

void	change_treck(void)
{
	if (g_b->treck < 3)
		++g_b->treck;
	else
		g_b->treck = 1;
	system("kill $(pgrep afplay) > /dev/null 2>&1");
	attron(COLOR_PAIR(1));
	if (g_b->treck == 1 && g_b->music)
	{
		system("afplay mp3/batle.mp3 &");
		mvprintw(g_b->bar_y_st + Y_MUSIC, X_BAR_SRT + 13, "%s ", TRECK1);
	}
	if (g_b->treck == 2 && g_b->music)
	{
		system("afplay mp3/cs.mp3 &");
		mvprintw(g_b->bar_y_st + Y_MUSIC, X_BAR_SRT + 13, "%s ", TRECK2);
	}
	if (g_b->treck == 3 && g_b->music)
	{
		system("afplay mp3/rk.mp3 &");
		mvprintw(g_b->bar_y_st + Y_MUSIC, X_BAR_SRT + 13, "%s ", TRECK3);
	}
	wrefresh(g_b->win);
}

/*
*** footbar in player_bar
*/

void	add_draw_playerbar(void)
{
	mvprintw(g_b->bar_y_st + Y_MUSIC, X_BAR_SRT, "%s", "TRACK NAME - ");
	attron(COLOR_PAIR(1));
	mvprintw(g_b->bar_y_st + Y_MUSIC, X_BAR_SRT + 13, "%s ", TRECK1);
	attron(COLOR_PAIR(15));
	mvprintw(g_b->bar_y_st + Y_ESC, X_BAR_SRT, "%s", "ESC        - "
												"exit program");
	mvprintw(g_b->bar_y_st + Y_SPACE, X_BAR_SRT, "%s", "SPACE      - "
												"running/pause");
	mvprintw(g_b->bar_y_st + Y_KEY_LEFT, X_BAR_SRT, "%s", "KEY_LEFT   - "
												"speed slowly");
	mvprintw(g_b->bar_y_st + Y_KEY_RIGHT, X_BAR_SRT, "%s", "KEY_RIGHT  - "
												"speed faster");
	mvprintw(g_b->bar_y_st + Y_KEY_UP, X_BAR_SRT, "%s", "KEY_UP     - "
												"change treck");
	mvprintw(g_b->bar_y_st + Y_KEY_DOWN, X_BAR_SRT, "%s", "KEY_DOWN   - "
															"music ");
	attron(COLOR_PAIR(1));
	mvprintw(g_b->bar_y_st + Y_KEY_DOWN, X_BAR_SRT + 19, "%s ", "ON  ");
}

/*
*** start_music
*/

void	start_music(void)
{
	attron(COLOR_PAIR(1));
	system("afplay mp3/batle.mp3 &");
	mvprintw(g_b->bar_y_st + Y_MUSIC, X_BAR_SRT + 13, "%s ", TRECK1);
}
