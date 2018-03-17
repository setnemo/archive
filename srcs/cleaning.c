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

static void	cleaning_read_room(t_lem *data)
{
	int a;

	a = 0;
	while (data->read_room[a])
	{
		free(data->read_room[a]);
		a++;
	}
	free(data->read_room);
	data->read_room = NULL;
}

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

static void	cleaning_xy_rooms(t_lem *data)
{
	int a;

	a = 0;
	while (a < data->how_rooms)
	{
		free(data->xy_rooms[a]);
		a++;
	}
	free(data->xy_rooms);
	data->xy_rooms = NULL;
}

void		cleaning(t_lem *data)
{
	if (data->line)
		free(data->line);
	if (data->rooms)
		free(data->rooms);
	if (data->temp)
		free(data->temp);
	if (data->read_room)
		cleaning_read_room(data);
	if (data->name_room)
		cleaning_name_room(data);
	if (data->links)
		cleaning_links(data);
	if (data->xy_rooms)
		cleaning_xy_rooms(data);
	cleaning_next(data);
	free(data);
	ft_printf("cleaning done\n");
}
