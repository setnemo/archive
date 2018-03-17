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

typedef struct	s_way
{
	int				*path;
	int				len;
	int				valid;
	struct s_way	*next;
}				t_way;

typedef struct	s_lem
{
	int				error;
	int				in;
	int				bound;
	int				countline;
	int				startroomline;
	int				firstroomline;
	size_t			how_ants;
	char			*input;
	char			*line;
	char			*rooms;
	char			*temp;
	char			**read_room;
	char			**name_room;
	int				**xy_rooms;
	int				**links;
	int				*tmp;
	int				how_rooms;
	int				start_room;
	int				start_count;
	int				end_count;
	int				end_room;
	int				how_path;
	int				*solve_path;
	struct s_way	*way;
}				t_lem;

void			cleaning(t_lem *data);
void			cleaning_next(t_lem *data);
void			manage_error(t_lem *data, int error);
void			manage_input(t_lem *data);
void			read_rooms(t_lem *data);



#endif
