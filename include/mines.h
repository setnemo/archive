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


typedef struct		s_img
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img_ptr;
	int				bpp;
	int				sl;
	int				endian;
}					t_img;

typedef struct		s_data
{
	struct s_img	*img;
}					t_data;

#endif
