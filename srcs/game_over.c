/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzamyati <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 12:09:20 by vzamyati          #+#    #+#             */
/*   Updated: 2018/07/22 12:09:23 by vzamyati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		game_over(t_data *data)
{
	int		ch;

	score2file(data);
	while (42)
	{
		check_size();
		get_clear();
		get_border();
		get_game_over_text(data);
		timeout(0);
		ch = getch();
		usleep(33333);
		data->win = 0;
		ch == '1' ? new_game(data) : 0;
		ch == '2' ? print_score(data) : 0;
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
	exit(0);
}

void		get_game_over_text(t_data *data)
{
	char	*sc;

	sc = ft_itoa(data->score);
	attron(COLOR_PAIR(1));
	mvprintw(C_J - 12, C_I - (ft_strlen("YOUR SCORE") / 2),
		"YOUR SCORE");
	attron(COLOR_PAIR(6));
	mvprintw(C_J - 10, C_I - (ft_strlen(sc) / 2), sc);
	ft_strdel(&sc);
	attron(COLOR_PAIR(2));
	mvprintw(C_J - 6, C_I - (ft_strlen("GAME OVER") / 2),
		"GAME OVER");
	attron(COLOR_PAIR(3));
	mvprintw(C_J - 3, C_I - (ft_strlen("Press 1 to NEW GAME") / 2),
		"Press 1 to NEW GAME");
	mvprintw(C_J, C_I - (ft_strlen("Press 2 to SCORE BOARD") / 2),
		"Press 2 to SCORE BOARD");
	mvprintw(C_J + 3, C_I - (ft_strlen("Press ESC to EXIT") / 2),
		"Press ESC to EXIT");
}
