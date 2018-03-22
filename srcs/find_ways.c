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

static void		breadthfirstsearch(t_lem *data)
{
	int a;
	int b;
	int c;
	int i;
	int j;
	int buf[data->how_rooms];

	ft_memset(buf, -1, (sizeof(int) * data->how_rooms));
	i = data->start_room;
	j = data->end_room;
	a = 0;
	b = 0;
	c = -1;
	b = 0;
	while (i != -1 && data->links[i][data->how_rooms] != -1)
	{
		a = 0;
		ft_printf("[%s] ==>", data->name_room[i]);
		while (a < data->how_rooms && i != data->end_room)
		{
			if (data->links[i][a] == 1 && data->links[a][data->how_rooms] != -1 && a != data->end_room)
			{
				buf[b] = a;
				ft_printf("[%s] ", data->name_room[buf[b]]);
				b++;
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
		// if (buf[c] != -1 && buf[c] < data->how_rooms)
		// 	ft_printf(":%s:\n", data->name_room[buf[c]]);
		// else
		// 	ft_printf(":...:\n");
	}
	ft_printf(":THE_END:\n");

}

void			find_way(t_lem *data)
{
	t_way		*ways;
	int			count;

	count = 0;
	ways = (t_way*)malloc(sizeof(t_way));
	data->way = ways;
	ft_bzero(ways, sizeof(t_way));
	ways->next = NULL;
	//ft_printf("%s", data->input);
	ft_printf("data->how_ants [%i]\n", data->how_ants);
	ft_printf("data->start_room [%i]\n", data->start_room);
	ft_printf("data->end_room [%i]\n", data->end_room);
	ft_printf("data->how_rooms [%i]\n", data->how_rooms);
	breadthfirstsearch(data);
}
