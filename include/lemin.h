/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:51:23 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/30 15:51:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_lst
{
	char			*str;
	char			*name;
	char			*name2;
	int				flag;
	int				x;
	int				y;
	struct s_lst	*next;
}				t_lst;

typedef struct	s_lem
{
	int				status;
	char			*line;
	size_t			how_ants;
	int				how_rooms;
	char			*input;
	char			*temp;
	int				error;
	int				stop;
	int				countline;
	int				start_count;
	int				end_count;
	struct s_lst	*next;
}				t_lem;

void			cleaning(t_lem *data);
void			check_ants(t_lem *data, int i);
void			write_input(t_lem *data);
void			manage_error(t_lem *data, int error);
void			manage_input(t_lem *data);

#endif
