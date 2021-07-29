/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greeting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzamyati <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:51:17 by vzamyati          #+#    #+#             */
/*   Updated: 2018/07/22 14:51:18 by vzamyati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		greeting(t_data *data)
{
	int		ch;

	while (42)
	{
		check_size();
		get_clear();
		get_border();
		get_greeting_text();
		timeout(0);
		ch = getch();
		usleep(33333);
		ch == '1' ? new_game(data) : 0;
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
	exit(0);
}

void		get_greeting_text(void)
{
	attron(COLOR_PAIR(3));
	mvprintw(C_J - 13, C_I - (ft_strlen("WELCOME TO") / 2),
		"WELCOME TO");
	attron(COLOR_PAIR(1));
	mvprintw(C_J - 11, C_I - 21, "   #######    #####   ##         #######  ");
	mvprintw(C_J - 10, C_I - 21, "  ##     ##  ##   ##  ##    ##  ##     ## ");
	mvprintw(C_J - 9, C_I - 21, "         ## ##     ## ##    ##  ##     ## ");
	mvprintw(C_J - 8, C_I - 21, "   #######  ##     ## ##    ##   #######  ");
	mvprintw(C_J - 7, C_I - 21, "  ##        ##     ## ######### ##     ## ");
	mvprintw(C_J - 6, C_I - 21, "  ##         ##   ##        ##  ##     ## ");
	mvprintw(C_J - 5, C_I - 21, "  #########   #####         ##   #######  ");
	attron(COLOR_PAIR(3));
	mvprintw(C_J, C_I - (ft_strlen("Press 1 to NEW GAME") / 2),
		"Press 1 to NEW GAME");
	attron(COLOR_PAIR(2));
	mvprintw(C_J + 6, C_I - (ft_strlen("Press ESC to EXIT") / 2),
		"Press ESC to EXIT");
	attron(COLOR_PAIR(1));
	mvprintw(C_J + 12, C_I - (ft_strlen("made by") / 2), "made by");
	attron(COLOR_PAIR(2));
	mvprintw(C_J + 13, C_I - (ft_strlen("apakhomo") / 2 - 1),
		"apakhomo");
	mvprintw(C_J + 14, C_I - (ft_strlen("vzamyati") / 2 - 1),
		"vzamyati");
}
