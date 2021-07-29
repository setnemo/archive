/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:02:30 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 13:02:31 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include <unistd.h>
# include "../libft/include/libft.h"
# include <fcntl.h>

/*
** ****************************************************************************
** **************************** struct for spot *******************************
** ****************************************************************************
*/

typedef struct	s_spt
{
	int				locx;
	int				locy;
	int				summ;
	struct s_spt	*next;
}				t_spt;

/*
** ****************************************************************************
** **************************** struct for bits *******************************
** ****************************************************************************
*/

typedef struct	s_bit
{
	int				ap;
	int				bp;
	int				bit_error;
	int				my_point;
	size_t			count;
	struct s_bit	*next;
}				t_bit;

/*
** ****************************************************************************
** **************************** struct for data *******************************
** ****************************************************************************
*/

typedef struct	s_fill
{
	char			xo;
	char			enemy;
	int				map_size[2];
	char			**map;
	int				bit_size[2];
	char			**bit;
	int				wait;
	int				fd;
	int				a_loc;
	int				b_loc;
	size_t			**matrix;
	int				ret;
	struct s_bit	*next;
	struct s_spt	*spot;
}				t_fill;

/*
** ****************************************************************************
** ******************************** start.c ***********************************
** ****************************************************************************
*/

void			start_play(t_fill *game);
void			read_map(t_fill *game);
void			read_bit(t_fill *game);
void			check_map(t_fill *game);

/*
** ****************************************************************************
** ******************************** fight.c ***********************************
** ****************************************************************************
*/

void			matrix_map(t_fill *g);
int				fill_point(t_fill *g, size_t *i, int a, int b);
void			matrix_fill_two(t_fill *g, size_t *i, char *flag);
void			matrix_fill_one(t_fill *g, size_t *i);
void			spot_loc(t_fill *g);

/*
** ****************************************************************************
** ******************************** spot.c ************************************
** ****************************************************************************
*/

void			find_lst(t_fill *g);
void			find_loc(t_fill *g);
t_bit			*check_bit_struct(t_bit *tbit, int a, int b);
void			check_bit(t_fill *g, t_bit *tbit, int a, int b);
void			find_spot(t_fill *g);

/*
** ****************************************************************************
** ******************************** free.c ************************************
** ****************************************************************************
*/

void			free_bit(t_fill *game);
void			free_map(t_fill *game);
void			free_sptlist(t_spt *lstsp);
void			free_bitlist(t_bit *lstsp);

#endif