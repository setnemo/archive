/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2048.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:46:44 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/23 17:46:44 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_2048_H
# define GAME_2048_H
# include "../libft/include/libft.h"
# include <ncurses.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <fcntl.h>

# define WIN_WIDTH 61
# define WIN_HEIGHT 31
# define HOWFOUR 20
# define WINSCORE 2048
# define C_I (COLS / 2)
# define C_J (LINES / 2)

typedef struct	s_data
{
	const char	*name;
	int			**core;
	int			field;
	int			colsfield;
	int			linesfield;
	int			score;
	int			random4[100];
	int			win;
}				t_data;

void			colors(void);
void			usage(void);

void			game_over(t_data *data);
void			get_game_over_text(t_data *data);

void			continue_game(t_data *data);
void			get_game_win_text(t_data *data);
void			game_win(t_data *data);

void			get_border(void);
void			get_clear(void);
void			get_numbers(t_data *data);
void			get_field(t_data *data, int i);
void			get_color(t_data *data, int i, int j);

void			greeting(t_data *data);
void			get_greeting_text(void);

void			init_data(t_data *data, int i, int x, int y);
void			init_ncurses(t_data *data);
void			new_game(t_data *data);

void			key_down(t_data *data);
void			key_up(t_data *data);
void			key_left(t_data *data);
void			key_right(t_data *data);

void			mv_numbers_down(t_data *data, int *count);
void			mv_numbers_up(t_data *data, int *count);
void			mv_numbers_left(t_data *data, int *count);
void			mv_numbers_right(t_data *data, int *count);

void			pause_menu(t_data *data);
void			pause_menu_text(void);

void			score2file(t_data *data);
void			print_score(t_data *data);
void			print_score2(t_data *data, int iter, int centerj, int centeri);
void			print_score3(t_data *data, int centerj, int centeri);
void			print_score_for_win(t_data *data, int centerj, int centeri);

void			sum_numbers_down(t_data *data);
void			sum_numbers_left(t_data *data);
void			plus_one(t_data *data, int x, int y);

void			check_size(void);
void			check_win(t_data *data);
void			fields_function(t_data *data, int *ch);
void			game_loop(t_data *data);

#endif
