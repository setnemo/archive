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

static void		sort_ants(t_lem *data, t_all *ways)
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
		ft_printf("%i:::\n", ways->len);
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

void		delete_nonvalid_path(t_lem *data, t_all *ways)
{
	t_all	*temp;

	while (ways)
	{
		if (ways->next)
		{
			if (ways->next->valid == 0)
			{
				ft_printf("free! %i\n", ways->next->valid);
				temp = ways->next->next;
				free(ways->next->path);
				free(ways->next);
				data->how_path -= 1;
				ways->next = temp;
			}
			if (ways->next)
				ways = ways->next;
			else
				break ;
		}
		else
			break ;
	}
}

static int	used_rooms(int *tmp, int use, t_lem *data)
{
	int i;

	i = 0;
	while (i < data->how_rooms && tmp[i] != -1 && use != data->start_room && use != data->end_room)
	{
		if (use == tmp[i])
			return (1);
		i++;
	}
	if (use != data->start_room && use != data->end_room){
	ft_printf("write used: %i\n", use);
		tmp[i] = use;}
	return (0);
}

void		mark_nonvalid_path(t_lem *data, t_all *ways)
{
	int	i;
	int	*inttempo;
	
	inttempo = (int*)malloc(sizeof(int) * (data->how_rooms));
	ft_memset((void*)inttempo, -1, (sizeof(int) * (data->how_rooms)));
	ways->valid = 1;
	t_all *nnn;
	nnn	= ways;
	int g;
	while (nnn)
	{
		g = 0;
		ft_printf("path: ");
		while (g < data->how_rooms)
		{
			ft_printf("%i ", nnn->path[g]);
			g++;
		}
		ft_printf("\n");
		if (nnn->next)
			nnn = nnn->next;
		else
			break;
	}
	nnn	= ways;
	while (ways)
	{
		i = 1;
		//ft_printf("::%i::__::%i::\n",ways->path[1], ways->next->path[1]);
		while(i < data->how_rooms - 1 && ways->path[i] != -1)
		{
			ft_printf("CHECKED NOW! ===>>> %i\n", ways->path[i]);
			if (used_rooms(inttempo, ways->path[i], data))
			{
				ft_printf("ENEMY DETECTED! ===>>> %i\n", ways->path[i]);
				ways->valid = 0;
				break ;
			}
			else
				ways->valid = 1;
			i++;
		}
		if (ways->next)
		{
			ways = ways->next;
		}
		else
			break;
	}
	while (nnn)
	{
		g = 0;
		ft_printf("path: ");
		while (g < data->how_rooms)
		{
			ft_printf("%i ", nnn->path[g]);
			g++;
		}
		ft_printf("\n");
		if (nnn->next)
			nnn = nnn->next;
		else
			break;
	}
	free (inttempo);
}


static int		sort_path_result(t_lem *data, t_all *ways)
{
	int 	tmp[data->how_rooms];
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
			break;
	}
	return (count);
}

static int		count_len_path(int *newpath)
{
	int i;

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
	ft_printf("save_path_to_result\n");

}

static void		ints_to_list_start(t_lem *data, t_way *ways, t_all *result)
{
	int i;

	i = 0;
	while (ways->path[i])
	{
		ft_printf("ways->path[%i]\n", i);
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
	// while (sort_path_result(data, result))
	// 	;
	mark_nonvalid_path(data, result);
	delete_nonvalid_path(data, result);
	while (sort_path_result(data, result))
		;
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
	result = data->alls;
	ft_printf("HOW PATH???[%i]\n", data->how_path);
	sort_ants(data, result);
	int i = 0;
	while (i < data->how_path * 3)
	{
		if (i == 2 || i == 5 || i == 8 || i == 11 || i == 14)
			ft_printf("|%i| ", data->solve_path[i]);
		else
			ft_printf("%i ", data->solve_path[i]);
		i++;
	}
}