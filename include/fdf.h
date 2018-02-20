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

typedef struct		s_brz
{
	int				px;
	int				py;
	int				dx;
	int				dy;
	int				xinc;
	int				yinc;
	unsigned long	pc;
}					t_brz;

typedef struct		s_map
{
	double			px;
	double			py;
	double			px1;
	double			py1;
	double			px2;
	double			py2;
	double			pz;
	unsigned long	pc;
	int				flag1;
	int				flag2;
	struct s_map	*next;
}					t_map;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	int				window;
	unsigned long	fill;
	int				fd;
	int				ret;
	char			*str;
	char			**map;
	int				how_x;
	int				how_y;
	int				iter;
	double			firstx;
	double			firsty;
	double			lastx;
	double			lasty;
	double			radx;
	double			rady;
	struct s_map	*line;
}					t_mlx;

void				free_data(t_mlx *data, int a);

int					check_flags(t_mlx *data, int argc, char **argv);

int					create_fdf_map(t_mlx *data, int a);

void			move_to_center(t_mlx *data);
void				start_fdf(t_mlx *data);

int					deal_key(int k, t_mlx *data);


#endif
