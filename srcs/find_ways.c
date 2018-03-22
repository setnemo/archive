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
}

static void		write_path_current(t_lem *data, t_way *ways, int i)
{
	if (data && ways && i)
		;
}


static void		write_path(t_lem *data, t_way *ways, int i, int flag)
{
	if (flag)
		write_path_current(data, ways, i);
	else
		write_path_new(data, ways, i);
}

static void		bfs(t_lem *data, int i, int c, int *buf)
{
	int a;
	int b;

	b = 0;
	while (i != -1 && data->links[i][data->how_rooms] != -1)
	{
		a = 0;
		ft_printf("[%s] ==>", data->name_room[i]);
		write_path(data, data->way, i, 0);
		while (a < data->how_rooms && i != data->end_room)
		{
			if (data->links[i][a] == 1 && data->links[a][data->how_rooms] != -1 && a != data->end_room)
			{
				buf[b] = a;
				write_path(data, data->way, a, 1);
				ft_printf("[%s] ", data->name_room[buf[b]]);
				b++;
			}
			if (data->links[i][a] == 1 && a == data->end_room)
			{
				write_path(data, data->way, a, 2);
				ft_printf("[%s] <<<<<", data->name_room[a]);
			}
			a++;
		}
		if (i != data->end_room)
		{
			data->links[i][data->how_rooms] = -1;
			ft_printf(".\n");
		}
		c++;
		i = buf[c];
	}
	ft_printf(":THE_END:\n");

}

void			find_way(t_lem *data)
{
	t_way		*ways;
	int			count;
	int			buf[data->how_rooms];

	count = 0;
	ways = (t_way*)malloc(sizeof(t_way));
	data->way = ways;
	ft_bzero(ways, sizeof(t_way));
	ft_memset(buf, -1, (sizeof(int) * data->how_rooms));
	//ft_printf("%s", data->input);
	ft_printf("data->how_ants [%i]\n", data->how_ants);
	ft_printf("data->start_room [%i]\n", data->start_room);
	ft_printf("data->end_room [%i]\n", data->end_room);
	ft_printf("data->how_rooms [%i]\n", data->how_rooms);
	bfs(data, data->start_room, -1, buf);
}
