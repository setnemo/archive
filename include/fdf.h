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

typedef  struct	s_mlx
{
	int		point[2];
	void	*mlx;
	void	*win;
	int		**loc;
	int		key;
	float	alt;
	float	zoom;
	int		y_loc;
	int		x_loc;
	int		isize;
	int		colour;
	int		peaks;
	int		rot;
	int		width;
	int		height;
	int		x;
	int		y;
}				t_mlx;

void	fdf(char *loc, t_mlx *input);
void	to_win(t_mlx *input);
void	ft_testintstr(int a, char *name);

#endif
