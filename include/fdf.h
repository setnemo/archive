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
# define X 0
# define Y 1
# define Z 2
# define C 3
# define FF 0xFFFFFF

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	int		point[2];
	int		**loc;
	int		key;
	float	alt;
	float	zoom;
	int		isize;
	int		colour;
	int		peaks;
	int		width;
	int		height;
	int		x;
	int		y;
	int		y_loc;
	int		x_loc;
}				t_mlx;

typedef struct	s_buf
{
	char	*line;
	char	*lbuf;
	char	*buf;
}				t_buf;

int				get_data(char *str);
int				get_map(char **str, int point[2], int fd, t_buf *buf);
void			exit_free(t_mlx *data);
void			restart(t_mlx *data);
int				deal_key(int key, t_mlx *data);
int				**get_loc(char *str, t_mlx *data, int i, int j);
void			fdf(char *str, t_mlx *data);
void			get_pixels(int *coords, int *pixel, t_mlx *data);
void			soft_line(int p1[4], int p2[4], void *mlx, void *win);
void			sharp_line(int p1[4], int p2[4], void *mlx, void *win);
void			draw_line(int p1[4], int p2[4], void *mlx, void *win);
void			to_window(t_mlx *data);

#endif
