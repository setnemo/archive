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
	int				stop;
	int				in;
	int				all;
	int				bound;
	int				countline;
	int				startroomline;
	int				firstroomline;
	int				endroomline;
	int				read_start;
	int				read_end;
	size_t			how_ants;
	char			*input;
	char			**validcoord;
	char			*line;
	char			*temp;
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

void			break_reading(t_lem *data, int error);
void			cleaning(t_lem *data);
void			cleaning_next(t_lem *data);
void			free_validcoord(t_lem *data);
void			manage_error(t_lem *data, int error);
void			manage_input(t_lem *data);
void			read_rooms(t_lem *data);
void			read_links(t_lem *data);
void			write_input(t_lem *data);
int				check_room_name(t_lem *data);
int				check_coords(t_lem *data, int i, int j);
int				check_coords_digits(char *line);

void			find_way(t_lem *data);

#endif
