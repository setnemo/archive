/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:38:13 by apakhomo          #+#    #+#             */
/*   Updated: 2018/07/21 15:38:16 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		check_size(void)
{
	if (COLS < WIN_WIDTH)
	{
		endwin();
		ft_printf("%s\n", "Too small window width!!!");
		exit(0);
	}
	if (LINES < WIN_HEIGHT)
	{
		endwin();
		ft_printf("%s\n", "Too small window height!!!");
		exit(0);
	}
}

void		get_game_win_text(t_data *data)
{
	int		centeri;
	int		centerj;
	char	*sc;

	sc = ft_itoa(data->score);
	centeri = COLS / 2;
	centerj = LINES / 2;
	attron(COLOR_PAIR(1));
	mvprintw(centerj - 12, centeri - (ft_strlen("YOUR SCORE") / 2), "YOUR SCORE");
	attron(COLOR_PAIR(6));
	mvprintw(centerj - 10, centeri - (ft_strlen(sc) / 2), sc);
	ft_strdel(&sc);
	attron(COLOR_PAIR(1));
	mvprintw(centerj - 6, centeri - (ft_strlen("CONGRATS!") / 2), "CONGRATS!");
	attron(COLOR_PAIR(3));
	mvprintw(centerj - 3, centeri - (ft_strlen("Press 1 to NEW GAME") / 2), "Press 1 to NEW GAME");
	mvprintw(centerj, centeri - (ft_strlen("Press 2 to SCORE BOARD") / 2), "Press 2 to SCORE BOARD");
	mvprintw(centerj + 3, centeri - (ft_strlen("Press ESC to EXIT") / 2), "Press ESC to EXIT");
}

void		game_win(t_data *data)
{
	int ch;

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
		ch == '1' ? new_game(data) : 0;
		if (ch == '2')
		{
			print_score(data);
			break ;
		}
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
	system("leaks -quiet game_2048");
	exit(0);
}

static void	check_win(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			if (WINSCORE == data->core[i][j])
				game_win(data);
		}
	}
}

static void	fields_function(t_data *data, int *ch)
{
	check_size();
	get_clear();
	get_field(data, 0);
	get_numbers(data);
	timeout(0);
	*ch = getch();
	usleep(33333);
}

void		game_loop(t_data *data)
{
	int ch;
	int count;

	while (42)
	{
		fields_function(data, &ch);
		count = 0;
		ch == KEY_DOWN ? key_down(data) : 0;
		ch == KEY_UP ? key_up(data) : 0;
		ch == KEY_LEFT ? key_left(data) : 0;
		ch == KEY_RIGHT ? key_right(data) : 0;
		check_win(data);
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
}
