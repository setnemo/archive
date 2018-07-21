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
# define WIN_WIDTH 21
# define WIN_HEIGHT 21
# define HOWFOUR 20

typedef struct 	s_data
{
	int			**core;
	int			field;
	int			colsfield;
	int			linesfield;
	int			random4[100];
}				t_data;


void			get_numbers(t_data *data);
void			get_clear(void);
void			get_field(t_data *data, int i);

void			mv_numbers_down(t_data *data);
void			mv_numbers_up(t_data *data);
void			mv_numbers_left(t_data *data);
void			mv_numbers_right(t_data *data);



void			game_loop(t_data *data);
void			check_size(void);


void			plus_one(t_data *data, int x, int y);

#endif
