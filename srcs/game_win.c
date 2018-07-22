/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_win.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzamyati <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 12:11:37 by vzamyati          #+#    #+#             */
/*   Updated: 2018/07/22 12:11:38 by vzamyati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		continue_game(t_data *data)
{
	int ch;

	while (42)
	{
		fields_function(data, &ch);
		ch == KEY_DOWN ? key_down(data) : 0;
		ch == KEY_UP ? key_up(data) : 0;
		ch == KEY_LEFT ? key_left(data) : 0;
		ch == KEY_RIGHT ? key_right(data) : 0;
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
}

void		get_game_win_text(t_data *data)
{
	char	*sc;

	sc = ft_itoa(data->score);
	attron(COLOR_PAIR(1));
	mvprintw(CENTER_J - 12, CENTER_I - (ft_strlen("YOUR SCORE") / 2),
		"YOUR SCORE");
	attron(COLOR_PAIR(6));
	mvprintw(CENTER_J - 10, CENTER_I - (ft_strlen(sc) / 2), sc);
	ft_strdel(&sc);
	attron(COLOR_PAIR(1));
	mvprintw(CENTER_J - 6, CENTER_I - (ft_strlen("CONGRATS!") / 2),
		"CONGRATS!");
	attron(COLOR_PAIR(3));
	mvprintw(CENTER_J - 3, CENTER_I - (ft_strlen("Press 1 to CONTINUE") / 2),
		"Press 1 to CONTINUE");
	mvprintw(CENTER_J, CENTER_I - (ft_strlen("Press 2 to NEW GAME") / 2),
		"Press 2 to NEW GAME");
	mvprintw(CENTER_J + 3, CENTER_I - (ft_strlen("Press 3 to SCORE BOARD") / 2),
		"Press 3 to SCORE BOARD");
	mvprintw(CENTER_J + 6, CENTER_I - (ft_strlen("Press ESC to EXIT") / 2),
		"Press ESC to EXIT");
}

void		game_win(t_data *data)
{
	int		ch;

	score2file(data);
	while (42)
	{
		check_size();
		get_clear();
		get_border();
		get_game_win_text(data);
		timeout(0);
		ch = getch();
		usleep(33333);
		ch == '1' ? continue_game(data) : 0;
		ch == '2' ? new_game(data) : 0;
		ch == '3' ? print_score(data) : 0;
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
	exit(0);
}
