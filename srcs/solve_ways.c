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
#define SZDHR sizeof(int) * data->how_rooms

static void		calculate_result_move(t_lem *data)
{
	int i;

	i = 2;
	while (i < data->how_path * 3)
	{
		if (data->solve_path[i - 1] != 0)
			data->solve_path[i] = data->solve_path[i - 2] +
		data->solve_path[i - 1] - 1;
		else
			data->solve_path[i] = 0;
		i += 3;
	}
}

static int		find_new_path(t_lem *data)
{
	int i;

	i = 2;
	while (i < data->how_path * 3)
	{
		if (data->solve_path[1] == 0)
			break ;
		if (i + 3 < data->how_path * 3)
		{
			if (data->solve_path[i] >= (data->solve_path[i + 1] +
				data->solve_path[i + 2]))
				return (i + 2);
			i += 3;
		}
		else
			break ;
	}
	return (1);
}

static void		sort_path_result(t_lem *data, t_way *ways)
{
	int i;
	int j;

	i = 0;
	data->solve_path = (int*)malloc(sizeof(int) * data->how_path * 3);
	ft_bzero(data->solve_path, sizeof(int) * data->how_path * 3);
	while (i < data->how_path * 3)
	{
		data->solve_path[i] = ways->len;
		i += 3;
		ways = ways->next;
	}
	j = data->how_ants;
	while (j--)
	{
		calculate_result_move(data);
		data->solve_path[find_new_path(data)]++;
		calculate_result_move(data);
	}
}

int				check_valid_path(t_lem *data, t_way *ways) // recode!!!!!!!!!!!!
{
	int		tmp[data->how_rooms];
	int		j;

	while (ways)
	{
		if (ways->next)
		{
			if (ways->path[0] == data->start_room &&
				ways->next->path[0] != data->start_room)
			{
				ft_memmove(&tmp, ways->next->path, SZDHR);
				j = 0;
				while (ways->path[j] != tmp[0])
					j++;
				ft_memmove(ways->next->path, ways->path, j);
				ft_memmove(&ways->next->path[j], &tmp, SZDHR - j - 1);
				j = 0;
				while (ways->next->path[j] != -1)
					ways->next->len = j++;
				return (1);
			}
		}
		ways = ways->next;
	}
	return (0);
}

void			solve_ways(t_lem *data, t_way *ways)
{
	t_way *test;

	test = ways;
	if (test)
		test++;
	int i = 0;
	// while (test)
	// {
	// 	i = 0;
	// 	ft_printf("path: ");
	// 	while (i < data->how_rooms)
	// 	{
	// 		ft_printf("%i ", test->path[i]);
	// 		i++;
	// 	}
	// 	ft_printf("\n");
	// 	if (test->next)
	// 		test = test->next;
	// 	else
	// 		break;
	// }
	ft_printf("LOL\n");
	mark_nonvalid_path(data, ways);
	delete_nonvalid_path(data, ways);
	sort_path_result(data, ways);
	//ft_printf("\n");
	i = 0;
	while (i < data->how_path * 3)
	{
		if (i == 2 || i == 5 || i == 8 || i == 11 || i == 14)
			ft_printf("|%i| ", data->solve_path[i]);
		else
			ft_printf("%i ", data->solve_path[i]);
		i++;
	}
}
