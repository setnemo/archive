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

static int		count_len_path(int *newpath)
{
	int i;

	i = 0;
	while (newpath[i] != -1)
		i++;
	return (i);
}

static void		save_path_to_result(t_lem *data, t_all *result, int *newpath)
{
	t_all	*temp;

	temp = result;
	while (temp)
	{
		if (temp->next)
			temp = temp->next;
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
	ft_printf("save_path_to_result\n");

}

static void		ints_to_list_start(t_lem *data, t_way *ways, t_all *result)
{
	int i;

	i = 0;
	while (ways->path[i])
	{
		ft_printf("ways->path[%i]\n", i);
		if (ways->path[i][0] > 0)
			save_path_to_result(data, result, ways->path[i]);
		i++;
	}
}

void			ints_to_list(t_lem *data)
{
	t_all		*result;

	result = data->alls;
	ints_to_list_start(data, data->way, result);
	while (result)
	{
		for (int i = 0; result->path[i] != -1; ++i)
		{
			ft_printf(" {%i} ", result->path[i]);
		}
		ft_printf("==LEN==>[%i]\n", result->len);
		if (result->next)
			result = result->next;
		else
			break ;
	}
}