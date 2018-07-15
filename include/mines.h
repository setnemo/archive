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
# include </root/libmlx/mlx.h>
// # include <mlx.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>
# define NOVICE_SIDE 9
# define NOVICE_MINES 10
# define INTER_SIDE 16
# define INTER_MINES 40
# define EXPERT_SIDE_X 30
# define EXPERT_SIDE_Y 16
# define EXPERT_MINES 99

typedef struct		s_img
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*smile;
	void			*xpm;
	int				*img_ptr;
	int				bpp;
	int				sl;
	int				endian;
	int				bpp_t;
	int				sl_t;
	int				endian_t;
	int				how_x;
	int				how_y;
	int				shiftx;
	int				shifty;
	int				fillcell;
	int				fillline;
	int				button[4];
	int				mines;
}					t_img;

typedef struct		s_data
{
	int				cellsize;
	int				bordersize;
	int				headersize;
	int				windowsizeh;
	int				windowsizew;
	int				status;
	int				start;
	int				openc;
	int				openm;
	time_t			times;
	time_t			sec;
	char			**field;
	char			**show;
	struct s_img	*img;
}					t_data;

int					window_close(void);
int					key_hook(int keycode, t_data *data);
int					mouse_hook(int mouse, int x, int y, t_data *data);

void				draw_square(t_img *img, t_data *data, int points[]);
void				draw_mines(t_data *data);

void				init_button(t_img *img, t_data *data, char *str);
void				init_lines(t_img *img, t_data *data);
void				init_img(t_data *data);

void				init_play_field(t_data *data, int x, int y);

void				solve_distance(t_data *data);
void				draw_xpm(t_data *data, int flag, int x, int y);


void		draw_stop(t_data *data, int flag);
#endif
