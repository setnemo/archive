/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzamyati <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 12:08:40 by vzamyati          #+#    #+#             */
/*   Updated: 2018/07/22 12:08:41 by vzamyati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		score2file(t_data *data)
{
	int		fd;
	char	*sc;

	fd = open("scores.txt", O_WRONLY | O_APPEND);
	if (fd < 0)
	{
		fd = open("scores.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644 | O_APPEND);
		if (fd < 0)
			ft_printf("Error fd open\n");
	}
	sc = ft_itoa(data->score);
	ft_putstr_fd(data->name, fd);
	ft_putstr_fd(" ", fd);
	ft_putendl_fd(sc, fd);
	free(sc);
	close(fd);
}

void		print_score(t_data *data)
{
	int		centeri;
	int		centerj;
	int		iter;

	get_clear();
	get_border();
	centeri = COLS / 2;
	centerj = LINES / 2;
	attron(COLOR_PAIR(1));
	iter = 0;
	centerj -= 12;
	mvprintw(centerj, centeri - (ft_strlen("SCORE BOARD") / 2),
		"SCORE BOARD");
	print_score2(data, iter, centerj, centeri);
}

void		print_score2(t_data *data, int iter, int centerj, int centeri)
{
	int		fd;
	char	*line;

	fd = open("scores.txt", O_RDONLY);
	attron(COLOR_PAIR(3));
	if (fd < 0)
		mvprintw(centerj - 11, centeri, "No data :(");
	else
	{
		centerj += 3;
		while (get_next_line(fd, &line) > 0)
		{
			iter += 2;
			mvprintw(centerj, centeri - (ft_strlen(line) / 2), line);
			ft_strdel(&line);
			centerj += 2;
			if (iter == 20)
				break ;
		}
	}
	close(fd);
	if (data->win == 0)
		print_score3(data, centerj, centeri);
	else if (data->win == 1)
		print_score_for_win(data, centerj, centeri);
}

void		print_score3(t_data *data, int centerj, int centeri)
{
	int		ch;

	attron(COLOR_PAIR(1));
	mvprintw(centerj, centeri - (ft_strlen("Press 1 for NEW GAME") / 2),
		"Press 1 for NEW GAME");
	attron(COLOR_PAIR(2));
	mvprintw(centerj + 2, centeri - (ft_strlen("Press ESC to EXIT") / 2),
		"Press ESC to EXIT");
	while (42)
	{
		ch = getch();
		ch == '1' ? new_game(data) : 0;
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
	exit(0);
}

void		print_score_for_win(t_data *data, int centerj, int centeri)
{
	int		ch;

	attron(COLOR_PAIR(1));
	mvprintw(centerj, centeri - (ft_strlen("Press 1 for CONTINUE") / 2),
		"Press 1 for CONTINUE");
	attron(COLOR_PAIR(3));
	mvprintw(centerj + 1, centeri - (ft_strlen("Press 2 for NEW GAME") / 2),
		"Press 2 for NEW GAME");
	attron(COLOR_PAIR(2));
	mvprintw(centerj + 2, centeri - (ft_strlen("Press ESC to EXIT") / 2),
		"Press ESC to EXIT");
	while (42)
	{
		ch = getch();
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
