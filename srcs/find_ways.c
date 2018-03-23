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

static void		write_path_new(t_lem *data, t_way *ways, int i)
{
	if (data && ways && i)
		;
	int a;
	int b;
	int r;

	r = 0;
	a = 0;
	while (ways->path[a])
	{
		b = 0;
		while (ways->path[a][b])
		{
			if (ways->path[a][b] == -1)
			{
				r = 1;
				break ;
			}
			b++;
		}
		if (r)
			break ;
		a++;
	}
	ways->path[a][b] = i;
}

static void		write_path_current(t_lem *data, t_way *ways, int i)
{
	if (data && ways && i)
		;

}


static void		write_path(t_lem *data, int i, int flag)
{
	if (flag)
		write_path_current(data, data->way, i);
	else
	{
		write_path_new(data, data->way, i);
	}
}

static int		new_room(int a, int *buf)
{
	int i;

i =0;
	while (buf[i] != -1)
	{
		if (buf[i] == a)
			return (0);
		i++;
	}
	return (1);
}

static void		bfs(t_lem *data, int i, int c, int *buf)
{
	int a;
	int b;

	b = 1;
	buf[c] = data->start_room;
	while (buf[c] != -1)
	{
		i = buf[c];
		ft_printf("======================[%s]==>", data->name_room[buf[c]]);
		a = 0;
		while (a < data->how_rooms)
		{
			if (data->links[i][a] == 1 && data->links[a][data->how_rooms] != -1 && a != data->end_room)
			{
				if (new_room(a, buf))
				{
					buf[b] = a;
					write_path(data, i, a);
					ft_printf(" [%s] ", data->name_room[buf[b]]);
					b++;
				}
			}
			if (data->links[i][a] == 1 && a == data->end_room)
			{
				write_path(data, a, 2);
				ft_printf("[%s] <<<<<", data->name_room[i]);
			}
			a++;
		}
		if (i != data->end_room)
		{
			data->links[i][data->how_rooms] = -1;
			ft_printf(".\n");
		}
		c++;
	}
	ft_printf(":THE_END:\n");
	for (int x = 0; x < data->how_rooms + 1; ++x)
	{
		if (buf[x] != -1)
			ft_printf("[%s] ", data->name_room[buf[x]]);
		else
		{
			ft_printf("[ ] ");
			break ;
		}
	}
	ft_printf("\n");
}

void			find_way(t_lem *data)
{
	t_way		*ways;
	int			count;
	int			buf[data->how_rooms*data->how_rooms];

	count = 0;
	ways = (t_way*)malloc(sizeof(t_way));
	data->way = ways;
	ft_bzero(ways, sizeof(t_way));
	ft_memset(buf, -1, (sizeof(int) * data->how_rooms + 1));
	ways->path = ft_new_int_arr(data->how_rooms * data->how_rooms);
	//ft_printf("%s", data->input);
	ft_printf("data->how_ants [%i]\n", data->how_ants);
	ft_printf("data->start_room [%i]\n", data->start_room);
	ft_printf("data->end_room [%i]\n", data->end_room);
	ft_printf("data->how_rooms [%i]\n", data->how_rooms);
	bfs(data, data->start_room, 0, buf);
}
