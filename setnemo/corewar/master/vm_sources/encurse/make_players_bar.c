/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_players_bar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:53:24 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/26 13:53:29 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_global	g_g;
extern t_curs	*g_b;

/*
*** make players
*/

static void	make_first_player(void)
{
	mvprintw(Y_BAR_PL1, X_BAR_SRT, "%s", "Player -1 : ");
	attron(COLOR_PAIR(1));
	mvprintw(Y_BAR_PL1, X_BAR_SRT + 12, "%.38s", g_g.players[0].name);
	attron(COLOR_PAIR(15));
	mvprintw(Y_BAR_PL1LL, X_BAR_SCL, "%s", "Last live : ");
	mvprintw(Y_BAR_PL1LIC, X_BAR_SCL, "%s", "Lives in current period : ");
}

static void	make_second_player(void)
{
	mvprintw(Y_BAR_PL2, X_BAR_SRT, "%s", "Player -2 : ");
	attron(COLOR_PAIR(2));
	mvprintw(Y_BAR_PL2, X_BAR_SRT + 12, "%.38s", g_g.players[1].name);
	attron(COLOR_PAIR(15));
	mvprintw(Y_BAR_PL2LL, X_BAR_SCL, "%s", "Last live : ");
	mvprintw(Y_BAR_PL2LIC, X_BAR_SCL, "%s", "Lives in current period : ");
}

static void	make_third_player(void)
{
	mvprintw(Y_BAR_PL3, X_BAR_SRT, "%s", "Player -3 : ");
	attron(COLOR_PAIR(3));
	mvprintw(Y_BAR_PL3, X_BAR_SRT + 12, "%.38s", g_g.players[2].name);
	attron(COLOR_PAIR(15));
	mvprintw(Y_BAR_PL3LL, X_BAR_SCL, "%s", "Last live : ");
	mvprintw(Y_BAR_PL3LIC, X_BAR_SCL, "%s", "Lives in current period : ");
}

static void	make_fifth_player(void)
{
	mvprintw(Y_BAR_PL4, X_BAR_SRT, "%s", "Player -4 : ");
	attron(COLOR_PAIR(4));
	mvprintw(Y_BAR_PL4, X_BAR_SRT + 12, "%.38s", g_g.players[3].name);
	attron(COLOR_PAIR(15));
	mvprintw(Y_BAR_PL4LL, X_BAR_SCL, "%s", "Last live : ");
	mvprintw(Y_BAR_PL4LIC, X_BAR_SCL, "%s", "Lives in current period : ");
}

void		show_players(void)
{
	if (g_b->pl_nb >= 1)
	{
		make_first_player();
		g_b->bar_y_st = Y_BAR_PL1;
	}
	if (g_b->pl_nb >= 2)
	{
		make_second_player();
		g_b->bar_y_st = Y_BAR_PL2;
	}
	if (g_b->pl_nb >= 3)
	{
		make_third_player();
		g_b->bar_y_st = Y_BAR_PL3;
	}
	if (g_b->pl_nb == 4)
	{
		make_fifth_player();
		g_b->bar_y_st = Y_BAR_PL4;
	}
	refresh();
}
