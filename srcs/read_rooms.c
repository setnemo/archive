/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define FCH ft_strchr

static void			save_rooms_coords(t_lem *data, char *p, int i)
{
	int a[2];

	data->xy_rooms[i] = a;
	data->xy_rooms[i][0] = ft_atoi(ft_strchr(p, 32));
	data->xy_rooms[i][1] = ft_atoi(ft_strrchr(p, 32));
}

static void			save_rooms_data(t_lem *data, int i, char *p)
{
	i = data->startroomline - 1;
	p = data->input;
	while (i)
	{
		if (*p == 10)
			i--;
		p++;
	}
	data->name_room = ft_new_char_arr(data->endroomline - data->startroomline);
	i = 0;
	while (*p)
	{
		if (*p != '#')
		{
			data->name_room[i] = (char*)malloc(sizeof(char) * (FCH(p, 10) - p) + 1);
			ft_strscpy(data->name_room[i], p, 32);
			save_rooms_coords(data, p, i);
			i++;
		}
		if (FCH(p, 10) != NULL)
			p = FCH(p, 10) + 1;
		else
			break ;
	}
	data->how_rooms = i;
}

static void			manage_start_end(t_lem *data)
{
	data->bound = ft_strequ(data->line, "##start") ? 1 : 2;
	if (data->bound == 1)
	{
		data->read_start = 1;
		data->start_count++;
		if (data->read_end)
			manage_error(data, 18);
	}
	else if (data->bound == 2)
	{
		data->read_end = 1;
		data->end_count++;
		if (data->read_start)
			manage_error(data, 19);
	}
}

static void			manage_room(t_lem *data)
{
	if (data->bound == 1)
		data->start_room = data->how_rooms;
	else if (data->bound == 2)
		data->end_room = data->how_rooms;
	data->how_rooms++;
	data->bound = 0;
	if (data->line[0] == 'L')
			manage_error(data, 5);
	if (data->start_count != 1 || data->end_count != 1)
	{
		if (data->read_start)
			data->read_start = 0;
		if (data->read_end)
			data->read_end = 0;
	}
	if (FCH(data->line, 32) == NULL ||
		FCH((FCH(data->line, 32)) + 1, 32) != ft_strrchr(data->line, 32) ||
		ft_strlen(ft_strchr(data->line, 32)) < 3)
		manage_error(data, 7);
	if (check_coords_digits(data->line))
		manage_error(data, 13);
	if (check_coords(data, 0, 0))
		manage_error(data, 12);
}

void				read_rooms(t_lem *data)
{
	if (ft_strchr(data->line, '-'))
	{
		data->in = 0;
		if (data->start_count != 1 || data->end_count != 1)
			manage_error(data, 4);
		data->endroomline = data->countline + 1;
		data->xy_rooms = ft_new_int_arr(data->endroomline - data->startroomline + 1);
		save_rooms_data(data, 0, NULL);
		//тут будет создание матрицы для сохранения линков
		read_links(data);
		return ;
	}
	write_input(data);
	if (ft_strequ(data->line, "##start") || ft_strequ(data->line, "##end"))
		manage_start_end(data);
	else if (data->line[0] == '#')
		;
	else
	{
		if (data->firstroomline)
		{
			data->startroomline = data->countline;
			data->firstroomline = 0;
		}
		manage_room(data);
	}
}