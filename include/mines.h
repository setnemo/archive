/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mines.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:46:44 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/23 17:46:44 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINES_H
# define MINES_H
# include "../libft/include/libft.h"
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# define X 0
# define Y 1
# define C 2

typedef struct		s_img
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*img_ptr;
	int				bpp;
	int				sl;
	int				endian;
	int				how_x;
	int				how_y;
	int				shiftx;
	int				shifty;
	int				fillcell;
	int				fillline;
}					t_img;

typedef struct		s_data
{
	int				cellsize;
	int				bordersize;
	int				headersize;
	int				windowsizeh;
	int				windowsizew;
	struct s_img	*img;
}					t_data;

int					window_close(void);
int					key_hook(int keycode);
void				init_img(t_data *data);
void				draw_line(int p1[3], int p2[3], t_img *img, int color);

#endif
