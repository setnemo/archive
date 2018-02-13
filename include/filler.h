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


#include <stdio.h>
#include <fcntl.h>

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
	struct s_bit 	*next;
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
	struct s_bit 	*next;
}				t_fill;

/*
** ****************************************************************************
** ******************************** start.c ***********************************
** ****************************************************************************
*/

void			start_filler(void);
void			start_play(t_fill *game);
void			read_map(t_fill *game);
void			read_bit(t_fill *game);
void			check_map(t_fill *game);

/*
** ****************************************************************************
** ******************************** fight.c ***********************************
** ****************************************************************************
*/

void		matrix_map(t_fill *g);
int			fill_point(t_fill *g, size_t *i, int a, int b);
void		matrix_fill_two(t_fill *g, size_t *i, char *flag);
void		matrix_fill_one(t_fill *g, size_t *i);
void		spot_loc(t_fill *g);
void		wait_enemy(t_fill *g);
#endif
