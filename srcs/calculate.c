/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define SZDHR sizeof(int) * data->how_rooms

static int		sort_path_result(t_lem *data, t_all *ways)
{
	int		tmp[data->how_rooms];
	int		count;

	count = 0;
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
				count++;
			}
			ways = ways->next;
		}
		else
			break ;
	}
	return (count);
}

static int		count_len_path(int *newpath)
{
	int		i;

	i = 0;
	while (newpath[i] != -1)
		i++;
	return (i - 1);
}

static void		save_path_to_result(t_lem *data, t_all *result, int *newpath)
{
	t_all	*temp;

	temp = result;
	while (temp)
	{
		if (temp->next)
		{
			temp = temp->next;
		}
		else
			break ;
	}
	if (temp->valid == 1)
	{
		temp->next = (t_all*)malloc(sizeof(t_all));
		temp->next->next = NULL;
		temp = temp->next;
		temp->path = (int*)malloc(sizeof(int) * (data->how_rooms + 1));
		ft_memset((void*)temp->path, -1, (sizeof(int) * (data->how_rooms + 1)));
		temp->valid = 1;
	}
	ft_memcpy(temp->path, newpath, sizeof(int) * (data->how_rooms + 1));
	temp->len = count_len_path(temp->path);
	temp->valid = 1;
}

static void		ints_to_list_start(t_lem *data, t_way *ways, t_all *result)
{
	int i;

	i = 0;
	while (ways->path[i])
	{
		if (ways->path[i][1] > -1)
		{
			data->how_path++;
			save_path_to_result(data, result, ways->path[i]);
		}
		i++;
	}
}

void			ints_to_list(t_lem *data)
{
	t_all		*result;

	result = data->alls;
	data->how_path = 0;
	ints_to_list_start(data, data->way, result);
	ft_printf("HOW PATH???[%i]\n", data->how_path);
	mark_nonvalid_path(data, result);
	delete_nonvalid_path(data, result);
	while (sort_path_result(data, result))
		;
	if (data->how_path == 0)
		manage_error(data, 22);
	sort_ants(data, result);
	ft_printf("HOW PATH???[%i]\n", data->how_path);
	int i = 0;
	while (i < data->how_path * 3)
	{
		if (i == 2 || i == 5 || i == 8 || i == 11 || i == 14)
			ft_printf("|%i| ", data->solve_path[i]);
		else
			ft_printf("%i ", data->solve_path[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("manage_output\n");
	manage_output(data);
}
