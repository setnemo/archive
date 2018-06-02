/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encurse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 13:39:23 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/03/18 13:39:25 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCURSE_H
# define ENCURSE_H

# include <stdlib.h>
# include <ncurses.h>
# include "vm.h"
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include <signal.h>

# define WIN_WIDTH 260
# define WIN_HEIGHT 70

# define X_MATR_SRT 4
# define Y_MATR_SRT 3
# define X_MATR_END 196
# define Y_MATR_END 68

# define X_BAR_SRT 206
# define Y_BAR_SRT 3
# define Y_BAR_SECL 5
# define Y_BAR_CYCL 9
# define Y_BAR_PROC 15

# define Y_BAR_PL1 17
# define Y_BAR_PL1LL 18
# define Y_BAR_PL1LIC 19
# define X_BAR_SCL 206

# define Y_BAR_PL2 21
# define Y_BAR_PL2LL 22
# define Y_BAR_PL2LIC 23

# define Y_BAR_PL3 25
# define Y_BAR_PL3LL 26
# define Y_BAR_PL3LIC 27

# define Y_BAR_PL4 29
# define Y_BAR_PL4LL 30
# define Y_BAR_PL4LIC 31

# define Y_BAR_CD 4
# define Y_BAR_CDEL 6
# define Y_BAR_NL 8
# define Y_BAR_MCH 10

# define Y_MUSIC 12

# define Y_ESC 15
# define Y_SPACE 16
# define Y_KEY_LEFT 17
# define Y_KEY_RIGHT 18
# define Y_KEY_UP 19
# define Y_KEY_DOWN 20

# define TRECK1 "Mortal Combat     "
# define TRECK2 "Counter Strike mix"
# define TRECK3 "Rocky eye of tiger"

typedef	struct	s_curs
{
	WINDOW		*win;
	int			pl_nb;
	int			bar_y_st;
	int			key;
	int			pause;
	int			cycle;
	int			music;
	int			treck;
	uint32_t	sleep;
	int			*map;
	int16_t		*live;
}				t_curs;

/*
*** init and first draw
*/

void			curse(void);
void			colors(void);
void			init_curs(void);
void			show_players(void);
void			make_bar(void);
void			make_border(void);

/*
*** redraw when game start
*/

void			print_map(void);
void			draw_new(int index);
void			erace_old(int index);
void			swap_cursor(int index);
void			readkey(void);
void			redraw_bar(void);
void			hooks(void);
void			load_player(int index, int player);
void			hotkey(void);
void			print_cursor(void);
void			call_me_baby_i_am_alive(int index);
void			redraw_player_bar(void);
void			add_draw_playerbar(void);
void			change_treck(void);
void			stop_music(void);
void			start_music(void);

/*
*** init and first draw
*/

void			ft_er_init(void);
void			ft_check_size_win(void);
void			exit_curse(void);
void			pashalka(void);
void			exit_curse_main(void);
void			siginthandler(int param);

#endif
