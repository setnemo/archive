/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define DLDHR data->links[bd->a][data->how_rooms] != -1
#define BDAER bd->a != data->end_room

void			write_input(t_lem *data)
{
	data->temp = ft_strjoin(data->input, data->line);
	ft_strdel(&data->input);
	data->input = ft_strjoin(data->temp, "\n");
	ft_strdel(&data->temp);
	data->countline++;
}

static int		new_room(int a, int *buf)
{
	int i;

	i = 0;
	while (buf[i] != -1)
	{
		if (buf[i] == a)
			return (0);
		i++;
	}
	return (1);
}

static void		bfs(t_lem *data, t_bfs *bd, int *buf)
{
	buf[bd->c] = data->start_room;
	while (buf[bd->c] != -1)
	{
		bd->i = buf[bd->c];
		bd->a = 0;
		while (bd->a < data->how_rooms)
		{
			if (data->links[bd->i][bd->a] == 1 && DLDHR && BDAER)
			{
				if (new_room(bd->a, buf))
				{
					buf[bd->b] = bd->a;
					write_path(data, bd->i, bd->a);
					bd->b++;
				}
			}
			if (data->links[bd->i][bd->a] == 1 && bd->a == data->end_room)
				write_path(data, bd->i, bd->a);
			bd->a++;
		}
		if (bd->i != data->end_room)
			data->links[bd->i][data->how_rooms] = -1;
		bd->c++;
	}
}

void			find_way(t_lem *data)
{
	t_way		*ways;
	t_bfs		bd;
	int			count;
	int			buf[data->how_rooms * data->how_rooms];

	count = 0;
	ways = (t_way*)malloc(sizeof(t_way));
	data->way = ways;
	ft_bzero(ways, sizeof(t_way));
	ft_memset(buf, -1, (sizeof(int) * (data->how_rooms + 1)));
	ways->path = ft_new_int_arr(data->how_rooms * data->how_rooms);
	bd.a = 0;
	bd.b = 1;
	bd.c = 0;
	bd.i = data->start_room;
	bfs(data, &bd, buf);
	manage_paths(data);
}
