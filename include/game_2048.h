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
# define WIN_WIDTH 61
# define WIN_HEIGHT 31
# define HOWFOUR 20

typedef struct 	s_data
{
	const char	*name;
	int			**core;
	int			field;
	int			colsfield;
	int			linesfield;
	int			score;
	int			random4[100];
}				t_data;

void			init_data(t_data *data, int i, int x, int y);
void			init_ncurses(t_data *data);
void			new_game(t_data *data);

void			get_numbers(t_data *data);
void			get_clear(void);
void			get_field(t_data *data, int i);

void			plus_one(t_data *data, int x, int y);
void			mv_numbers_down(t_data *data, int *count);
void			mv_numbers_up(t_data *data, int *count);
void			mv_numbers_left(t_data *data, int *count);
void			mv_numbers_right(t_data *data, int *count);

void			get_color(t_data *data, int i, int j);

void			game_loop(t_data *data);
void			check_size(void);

void			sum_numbers_down(t_data *data);
void			sum_numbers_left(t_data *data);

void 			key_down(t_data *data);
void			key_up(t_data *data);
void			key_left(t_data *data);
void			key_right(t_data *data);

void			game_over(t_data *data);
void			colors(void);

#endif
