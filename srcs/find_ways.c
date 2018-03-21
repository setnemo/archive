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
	c = 0;
	ft_printf("data----\n");
	while (i != j)
	{
		a = 0;
		while (a < data->how_rooms)
		{
			if (data->links[i][a] == 1)
			{
				buf[b] = a;
				ft_printf("[%s] ", data->name_room[buf[b]]);
			}
			a++;
		}
		ft_printf("\n");
		// while (buf[c] == -1 && c < data->how_rooms)
		c++;
		if (buf[c] == j)
			break ;
		i = buf[c];
		buf[c] = -1;
	}	
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
	ft_printf("%s", data->input);
	ft_printf("data->how_ants [%i]\n", data->how_ants);
	ft_printf("data->start_room [%i]\n", data->start_room);
	ft_printf("data->end_room [%i]\n", data->end_room);
	ft_printf("data->how_rooms [%i]\n", data->how_rooms);
	breadthfirstsearch(data);
}
