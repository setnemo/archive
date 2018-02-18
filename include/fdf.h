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

typedef struct		s_map
{
	int				px1;
	int				py1;
	int				px2;
	int				py2;
	int				pz;
	unsigned long	pc;
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
	struct s_map	*line;
}					t_mlx;

void				free_data(t_mlx *data, int a);

int					check_flags(t_mlx *data, int argc, char **argv);

int					create_fdf_map(t_mlx *data, int a);

#endif
