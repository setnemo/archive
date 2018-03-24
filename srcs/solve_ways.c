/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_ways.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define SZDHR sizeof(int) * (data->how_rooms)

static void		no_start_end_help(t_way *ways, int j, int i)
{
	while (j != 0)
	{
		ways->path[i][j] = -1;
		j--;
	}
	while (ways->path[i][j]--)
		;
	ways->path[i][j] -= 1;
}

static void		no_start_end(t_lem *data, t_way *ways, int start, int end)
{
	int i;
	int j;
	
	i = 0;
	while (ways->path[i] != NULL && ways->path[i][0] != -1)
	{
		start = 0;
		end = 0;
		j = 0;
		if (ways->path[i][j] == data->start_room)
			start = 1;
		while (j < data->how_rooms)
		{
			if (ways->path[i][j] == data->end_room)
				end = 1;
			j++;
		}
		if (end != 1 || start != 1)
			no_start_end_help(ways, j, i);
		i++;
	}
}

static void		move_path(t_lem *data, t_way *ways, int i, int flag)
{
	while (flag)
	{
		flag = 0;
		while (ways->path[i + 1])
		{
			while (ways->path[i][0] != -1 && i - 1 > 0 && ways->path[i - 1][0] == -1)
			{
				ft_memmove(ways->path[i - 1], ways->path[i], SZDHR);
				ft_memset(ways->path[i], -1, (sizeof(int) * (data->how_rooms + 1)));
				flag++;
				i = 0;
			}
			i++;
		}
	}
}

static void		delete_wrong_path(t_lem *data, t_way *ways)
{
	int i;
	int flag;
	int j;

	no_start_end(data, ways, 0, 0);
	flag = 1;
	i = 0;
	while (ways->path[i])
	{
		j = 1;
		while (ways->path[i + j])
		{
			if (ft_memcmp(ways->path[i], ways->path[i + j], SZDHR) == 0)
				ft_memset(ways->path[i + j], -1, 
					(sizeof(int) * (data->how_rooms + 1)));
			j++;
		}
		i++;
	}
	move_path(data, ways, 0, 1);
}

void			manage_paths(t_lem *data)
{
	t_way		*ways;
	int			i;
	t_all		*result;
	
	ways = data->way;
	delete_wrong_path(data, ways);
	i = 0;
	while (ways->path[i])
	{
		if (ways->path[i][0] == - 1)
		{
			free(ways->path[i]);
			ways->path[i] = NULL;
		}
		i++;
	}
	result = (t_all*)malloc(sizeof(t_all));
	data->alls = result;
	ft_bzero(result, sizeof(t_all));
	result->next = NULL;
	result->path = (int*)malloc(sizeof(int) * (data->how_rooms + 1));
	ft_memset((void*)result->path, -1, (sizeof(int) * (data->how_rooms + 1)));
	result->valid = 1;
	ints_to_list();
	

	// for (int x = 0; x < data->how_rooms + 1; ++x)
	// {
	// 	if (data->way->path[x])
	// 	{

	// 		for (int m = 0; m < data->how_rooms; ++m)
	// 		{
	// 			// if (data->way->path[x])
	// 			// 	ft_printf("[%i]:", data->way->path[x][m]);
	// 			//if (data->name_room[data->way->path[x][m]])
	// 				ft_printf("[%i] ", data->way->path[x][m]);
	// 		}
	// 		ft_printf("\n");
	// 	}
	// 	else
	// 	{
	// 		ft_printf("[ ] ");
	// 		break ;
	// 	}
	// }
	// ft_printf("\n");
}