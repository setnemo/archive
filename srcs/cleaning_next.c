/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	cleaning_way(t_way *ways)
{
	t_way *temp;

	while (ways)
	{
		free(ways->path);
		if (ways->next)
		{
			temp = ways;
			ways = ways->next;
			free(temp);
		}
		else
		{
			free(ways);
			ways = NULL;
		}
	}
}

static void	cleaning_validcoord(t_lem *data)
{
	int a;

	a = 0;
	while (data->validcoord[a])
	{
		free(data->validcoord[a]);
		a++;
	}
	free(data->validcoord);
	data->validcoord = NULL;
}

void		cleaning_next(t_lem *data)
{
	if (data->way)
		cleaning_way(data->way);
	if (data->validcoord)
		cleaning_validcoord(data);
	if (data->solve_path)
		free(data->solve_path);
	if (data->tmp)
		free(data->tmp);
}

void		free_validcoord(t_lem *data)
{
	int a;

	a = 0;
	while (data->validcoord[a])
	{
		free(data->validcoord[a]);
		a++;
	}
	free(data->validcoord);
	data->validcoord = NULL;
}

void		delete_nonvalid_path(t_lem *data, t_way *ways)
{
	t_way	*temp;

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

void		mark_nonvalid_path(t_lem *data, t_way *ways)
{
	int	i;
	
	data->tmp = (int*)malloc(sizeof(int) * (data->how_rooms));
	ft_memset((void*)data->tmp, -1, (sizeof(int) * (data->how_rooms)));
	ways->valid = 1;
	t_way *nnn;
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
			if (used_rooms(data->tmp, ways->path[i], data))
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
}
