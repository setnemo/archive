/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ants.c                                        :+:      :+:    :+:   */
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

void			sort_ants(t_lem *data, t_all *ways)
{
	int i;
	int j;

	i = 0;
	if ((int)data->how_ants < data->how_path)
		data->how_path = data->how_ants;
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

static int		used_rooms(int *tmp, int use, t_lem *data)
{
	int i;

	i = 0;
	while (i < data->how_rooms && tmp[i] != -1 &&
		use != data->start_room && use != data->end_room)
	{
		if (use == tmp[i])
			return (1);
		i++;
	}
	if (use != data->start_room && use != data->end_room)
		tmp[i] = use;
	return (0);
}

void			mark_nonvalid_path(t_lem *data, t_all *ways)
{
	int		i;
	int		*inttempo;

	inttempo = (int*)malloc(sizeof(int) * (data->how_rooms));
	ft_memset((void*)inttempo, -1, (sizeof(int) * (data->how_rooms)));
	while (ways)
	{
		i = 1;
		while (i < data->how_rooms - 1 && ways->path[i] != -1)
		{
			if (used_rooms(inttempo, ways->path[i], data))
			{
				ways->valid = 0;
				break ;
			}
			else
				ways->valid = 1;
			i++;
		}
		if (ways->next)
			ways = ways->next;
		else
			break ;
	}
	free(inttempo);
}
