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

typedef struct	s_wp
{
	int				a;
	int				b;
	int				addnew;
	int				flag;
	int				**allpath;
}				t_wp;

typedef struct	s_bfs
{
	int				a;
	int				b;
	int				c;
	int				i;
}				t_bfs;

typedef struct	s_all
{
	int				*path;
	int				len;
	int				valid;
	struct s_all	*next;
}				t_all;

typedef struct	s_way
{
	int				**path;
	int				*len;
	int				check;
}				t_way;

typedef struct	s_lem
{
	int				error;
	int				stop;
	int				in;
	int				all;
	int				bound;
	int				showinput;
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
	struct s_all	*alls;
}				t_lem;

void			break_reading(t_lem *data, int error);
void			cleaning(t_lem *data);
void			cleaning_next(t_lem *data);
void			free_validcoord(t_lem *data);
void			delete_nonvalid_path(t_lem *data, t_all *ways);

void			manage_error(t_lem *data, int error);
void			manage_input(t_lem *data);
void			read_rooms(t_lem *data);
void			read_links(t_lem *data);
int				check_room_name(t_lem *data);
int				check_coords(t_lem *data, int i, int j);
int				check_coords_digits(char *line);

void			write_input(t_lem *data);
void			find_way(t_lem *data);

void			manage_paths(t_lem *data);

void			ints_to_list(t_lem *data);

void			sort_ants(t_lem *data, t_all *ways);
void			mark_nonvalid_path(t_lem *data, t_all *ways);

void			last_room(t_lem *data);
void			write_path(t_lem *data, int i, int j);

#endif
