/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	cleaning_name_room(t_lem *data)
{
	int a;

	a = 0;
	while (data->name_room[a])
	{
		free(data->name_room[a]);
		a++;
	}
	free(data->name_room);
	data->name_room = NULL;
}

static void	cleaning_links(t_lem *data)
{
	int a;

	a = 0;
	while (a < data->how_rooms + 1)
	{
		free(data->links[a]);
		a++;
	}
	free(data->links);
	data->links = NULL;
}

void		cleaning(t_lem *data)
{
	if (data->input)
		free(data->input);
	if (data->line)
		free(data->line);
	if (data->temp)
		free(data->temp);
	if (data->name_room)
		cleaning_name_room(data);
	if (data->links)
		cleaning_links(data);
	if (data->xy_rooms)
		free(data->xy_rooms);
	cleaning_next(data);
	free(data);
	ft_printf("cleaning done\n");
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
