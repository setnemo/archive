/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzamyati <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 14:52:14 by vzamyati          #+#    #+#             */
/*   Updated: 2018/07/22 14:52:15 by vzamyati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		pause_menu(t_data *data)
{
	int		ch;

	while (42)
	{
		check_size();
		get_clear();
		get_border();
		pause_menu_text();
		timeout(0);
		ch = getch();
		usleep(33333);
		ch == '1' ? continue_game(data) : 0;
		ch == '2' ? new_game(data) : 0;
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
	exit(0);
}

void		pause_menu_text(void)
{
	attron(COLOR_PAIR(1));
	mvprintw(CENTER_J - 11, CENTER_I - 17, "  #####    ###   #        ##### ");
	mvprintw(CENTER_J - 10, CENTER_I - 17, " #     #  #   #  #    #  #     # ");
	mvprintw(CENTER_J - 9, CENTER_I - 17, "       # #     # #    #  #     # ");
	mvprintw(CENTER_J - 8, CENTER_I - 17, "  #####  #     # #    #   #####  ");
	mvprintw(CENTER_J - 7, CENTER_I - 17, " #       #     # ####### #     # ");
	mvprintw(CENTER_J - 6, CENTER_I - 17, " #        #   #       #  #     # ");
	mvprintw(CENTER_J - 5, CENTER_I - 17, " #######   ###        #   #####  ");
	mvprintw(CENTER_J, CENTER_I - (ft_strlen("Press 1 to CONTINUE") / 2),
		"Press 1 to CONTINUE");
	attron(COLOR_PAIR(3));
	mvprintw(CENTER_J + 3, CENTER_I - (ft_strlen("Press 2 to NEW GAME") / 2),
		"Press 2 to NEW GAME");
	attron(COLOR_PAIR(2));
	mvprintw(CENTER_J + 6, CENTER_I - (ft_strlen("Press ESC to EXIT") / 2),
		"Press ESC to EXIT");
}
