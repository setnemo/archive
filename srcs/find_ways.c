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
#define SZDHR sizeof(int) * data->how_rooms

static void		sort_path_result(t_lem *data, t_way *ways)
{
	int 	tmp[data->how_rooms];

	while (ways)
	{
		if (ways->next)
		{
			if (ways->len > ways->next->len)
			{
				ft_swap(&ways->len, &ways->next->len);
				ft_memmove(&tmp, ways->path, SZDHR);
				ft_memmove(ways->path, ways->next->path, SZDHR);
				ft_memmove(ways->next->path, &tmp, SZDHR);
			}
			ways = ways->next;
		}
		else
			break;
	}
}

static t_way	*search_tway(t_lem *data, t_way *ways, int j)
{
	while (j--)
	{
		if (ways->next == NULL)
		{
			ways->next = (t_way*)malloc(sizeof(t_way));
			ft_bzero(ways->next, sizeof(t_way));
			ways->next->next = NULL;
			ways->next->path = (int*)malloc(sizeof(int) * (data->how_rooms + 1));
			ft_memset((void*)ways->next->path, -1, 
				(sizeof(int) * (data->how_rooms + 1)));
			ways = ways->next;
			ways->valid = 1;
		}
		else
			ways = ways->next;
	}
	return (ways);
}

static void		write_way(t_lem *data, int id, int i, int *count)
{
	int		j;
	t_way	*ways;

	ways = data->way;
	j = *count;
	if (*count > 0)
		ways = search_tway(data, ways, j);
	if (ways->path[0] == -1)
	{
		ways->path[0] = id;
		ways->path[1] = i;
	}
	else
	{
		ft_printf("WRITE NOW (id==%i) (i==%i) ", id, i);
		j = 0;
		while (ways->path[j] != -1){
			ft_printf("[%i] ", ways->path[j]);
			j++;
			if (j > 1 && (i == ways->path[j - 1] || id == ways->path[j - 2]))
			{
				ways->path[j - 2] = i;
				ways->path[j - 1] = id;
				ways->len = j;
				return ;
			}
		}
		ways->path[j - 1] = id;
		ways->path[j] = i;
		ways->len = j;
		ft_printf(" _[%i]__[%i]_\n", ways->path[j - 1], ways->path[j]);
	}
}

static void		check_link_way(t_lem *data, int id, int *count)
{
	int i;

	i = 0;
	if (data->links[id][data->how_rooms] != -1)
	{
		data->links[id][data->how_rooms] = -1;
		while (i < data->how_rooms)
		{
			if (data->links[id][i] == 1)
			{
				data->links[i][id] = 0;
				write_way(data, id, i, count);
				if (i == data->end_room)
				{					
					(*count)++;
					data->links[i][id] = 1;
					return ;
				}
				check_link_way(data, i, count); // дописать конкатенацию путей-развилок
				data->links[i][id] = 1;
			}
			i++;
		}
		data->links[id][data->how_rooms] = 0;
		data->how_path = *count;
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
	ways->path = (int*)malloc(sizeof(int) * (data->how_rooms + 1));
	ft_memset((void*)ways->path, -1, (sizeof(int) * (data->how_rooms + 1)));
	ways->valid = 1;
	check_link_way(data, data->start_room, &count);
	ways = data->way;
	while (check_valid_path(data, ways))
		;
	sort_path_result(data, ways);
	sort_path_result(data, ways);
	solve_ways(data, ways);
	int i = 0;
	while (ways)
	{
		i= 0;
		ft_printf("\n");
		while (ways->path[i] != -1)
		{
			ft_printf("[%s] ", data->name_room[ways->path[i]]);
			i++;
		}
		ft_printf("\n", ways->len);

		if (ways->next)
			ways = ways->next;
		else
			break ;
	}
	ft_printf("%i path in list\n", data->how_path);
}
