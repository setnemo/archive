/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 14:45:00 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/26 14:45:02 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encurse.h"

extern t_global	g_g;
extern t_curs	*g_b;

static void	print_color_p1(int *i)
{
	wattron(g_b->win, COLOR_PAIR(1));
	while (*i < g_g.players[0].startpos + g_g.players[0].field_size)
	{
		wprintw(g_b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(g_b->win, "\n");
		(*i)++;
	}
	wattron(g_b->win, COLOR_PAIR(14));
}

static void	print_color_p2(int *i)
{
	wattron(g_b->win, COLOR_PAIR(2));
	while (*i < g_g.players[1].startpos + g_g.players[1].field_size)
	{
		wprintw(g_b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(g_b->win, "\n");
		(*i)++;
	}
	wattron(g_b->win, COLOR_PAIR(14));
}

static void	print_color_p3(int *i)
{
	wattron(g_b->win, COLOR_PAIR(3));
	while (*i < g_g.players[2].startpos + g_g.players[2].field_size)
	{
		wprintw(g_b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(g_b->win, "\n");
		(*i)++;
	}
	wattron(g_b->win, COLOR_PAIR(14));
}

static void	print_color_p4(int *i)
{
	wattron(g_b->win, COLOR_PAIR(4));
	while (*i < g_g.players[3].startpos + g_g.players[3].field_size)
	{
		wprintw(g_b->win, " %02x", g_g.field[*i]);
		if (*i % 64 == 63)
			wprintw(g_b->win, "\n");
		(*i)++;
	}
	wattron(g_b->win, COLOR_PAIR(14));
}

void		print_map(void)
{
	int		i;

	i = -1;
	wattron(g_b->win, COLOR_PAIR(14));
	refresh();
	while (++i < MEM_SIZE)
	{
		if (i == g_g.players[0].startpos)
			print_color_p1(&i);
		else if (i == g_g.players[1].startpos)
			print_color_p2(&i);
		else if (i == g_g.players[2].startpos)
			print_color_p3(&i);
		else if (i == g_g.players[3].startpos)
			print_color_p4(&i);
		wprintw(g_b->win, " %02x", g_g.field[i]);
		if (i % 64 == 63)
			wprintw(g_b->win, "\n");
	}
	wrefresh(g_b->win);
}
