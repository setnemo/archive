/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:51:23 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/30 15:51:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# define FT_ROT(x) ft_rot_x(x); ft_rot_y(x); ft_rot_z(x);
# define FT_CHECK_BUF " 0123456789-ABCDEFabcdef,x\n"
# define SIGN(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0));

typedef struct	s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef struct	s_info
{
	float		dx;
	float		dy;
	float		x;
	float		y;
	float		d;
	float		s1;
	float		s2;
	float		swap;
	float		tmp;
}				t_info;

typedef struct	s_total
{
	int			fd;
	void		*mlx;
	void		*win;
	t_point		**pt;
	t_point		**ptdup;
	t_info		info;
	int			**map;
	float		pic_wid;
	float		pic_hgt;
	int			def_wid;
	int			def_hgt;
	float		st_x;
	float		st_y;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	int			max_z;
	int			min_z;
	float		z_scale;
	int			expose;
	float		move_x;
	float		move_y;
	float		zoom;
	int			red;
	int			color;
}				t_total;

void			ft_read_file(char **av, t_total *tot);
int				ft_read_line(char **av, t_total *tot);
void			ft_read_buf(char *str);
void			ft_read_allocate(t_total *tot);
void			ft_read_tmp(char **tmp, t_total *tot, int j);

/*
** ft_error.c
*/
void			ft_error_msg(char *str);

/*
** ft_window.c
*/
int				ft_window_key(int keycode, t_total *tot);
int				ft_window_expose(t_total *tot);
void			ft_window_move(int keycode, t_total *tot);
void			ft_window_alt(int keycode, t_total *tot);

/*
** ft_mvmt.c
*/
void			ft_rot_x(t_total *tot);
void			ft_rot_y(t_total *tot);
void			ft_rot_z(t_total *tot);

/*
** ft_plot.c
*/
void			ft_plot_setup(t_total *tot);
void			ft_plot_dup(t_total *tot);
void			ft_plot_pt(t_total *tot);
void			ft_plot_connect(t_total *tot, t_point pt1, t_point pt2);
void			ft_plot_prep(t_total *tot, t_point pt1, t_point pt2);

/*
** ft_init.c
*/
void			ft_init_val(t_total *tot);
void			ft_init_reset(t_total *tot);
void			ft_init_msg(t_total *tot);
void			ft_init_color_x(t_total *tot, int x, int y);
void			ft_init_color_y(t_total *tot, int x, int y);

#endif
