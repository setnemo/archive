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
// #define DRR data->read_room
// #define FCH ft_strchr

// static int		other_rooms(t_lem *data, int *count)
// {
// 	if (data->line[0] == '#')
// 	{
// 		ft_strdel(&data->line);
// 		get_next_line(STDIN_FILENO, &data->line);
// 	}
// 	else
// 	{
// 		if (ft_strchr(data->line, '-') || *data->line == 0)
// 			return (1);
// 		data->temp = ft_strjoin_free(data->rooms, data->line);
// 		data->rooms = ft_strjoin(data->temp, "\n");
// 		ft_strdel(&data->temp);
// 		*count += 1;
// 	}
// 	return (0);
// }

// static int		check_bound(t_lem *data, int flag, int *count)
// {
// 	flag = ft_strequ(data->line, "##start") ? 1 : 0;
// 	ft_strdel(&data->line);
// 	if (get_next_line(STDIN_FILENO, &data->line) < 1 || *data->line == 0)
// 		return (1);
// 	if (data->line[0] == '#')
// 		manage_error(data, 4);
// 	if (flag)
// 	{
// 		data->start_room = *count;
// 		data->start_count++;
// 	}
// 	else
// 	{
// 		data->end_room = *count;
// 		data->end_count++;
// 	}
// 	*count += 1;
// 	data->temp = ft_strjoin_free(data->rooms, data->line);
// 	data->rooms = ft_strjoin(data->temp, "\n");
// 	ft_strdel(&data->temp);
// 	return (0);
// }

// static void		fill_name_room_array(t_lem *data)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (data->read_room[i])
// 	{
// 		data->name_room[i] = ft_strsub(DRR[i], 0, FCH(DRR[i], 32) - DRR[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (data->name_room[i])
// 	{
// 		j = 1;
// 		if (ft_strchr(data->name_room[i], '-') || data->name_room[i][0] == 'L')
// 			manage_error(data, 5);
// 		while (data->name_room[i + j])
// 		{
// 			if (ft_strequ(data->name_room[i], data->name_room[i + j]))
// 				manage_error(data, 5);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void		validation_rooms(t_lem *data)
// {
// 	int i;

// 	i = 0;
// 	data->read_room = ft_strsplit(data->rooms, 10);
// 	data->how_rooms = ft_count_to_null((void**)data->read_room, 0);
// 	if (data->how_rooms > 1000)
// 		manage_error(data, 6);
// 	data->name_room = ft_new_char_arr((size_t)data->how_rooms);
// 	data->xy_rooms = ft_new_int_arr((size_t)data->how_rooms);
// 	fill_name_room_array(data);
// 	while (i < data->how_rooms)
// 	{
// 		data->xy_rooms[i] = (int*)malloc(sizeof(int) * 2);
// 		ft_bzero(data->xy_rooms[i], sizeof(int) * 2);
// 		if (FCH((FCH(DRR[i], 32)) + 1, 32) != ft_strrchr(DRR[i], 32) ||
// 			ft_strlen(ft_strchr(data->read_room[i], 32)) < 3)
// 			manage_error(data, 7);
// 		data->xy_rooms[i][0] = ft_atoi(ft_strchr(data->read_room[i], 32));
// 		data->xy_rooms[i][1] = ft_atoi(ft_strrchr(data->read_room[i], 32));
// 		if (data->xy_rooms[i][0] < 0 || data->xy_rooms[i][1] < 0)
// 			manage_error(data, 7);
// 		i++;
// 	}
// }

// void			read_rooms(t_lem *data, int count)
// {
// 	data->rooms = ft_strnew(0);
// 	while ((get_next_line(STDIN_FILENO, &data->line)) > 0)
// 	{
// 		if (ft_strchr(data->line, '-'))
// 			break ;
// 		while (data->line[0] == '#' && data->line[1] != '#')
// 		{
// 			ft_strdel(&data->line);
// 			if (get_next_line(STDIN_FILENO, &data->line) < 1)
// 				break ;
// 		}
// 		if (ft_strequ(data->line, "##start") || ft_strequ(data->line, "##end"))
// 		{
// 			if (check_bound(data, 0, &count))
// 				break ;
// 		}
// 		else
// 		{
// 			if (other_rooms(data, &count))
// 				break ;
// 		}
// 	}
// 	if (data->start_count != 1 || data->end_count != 1)
// 		manage_error(data, 4);
// 	validation_rooms(data);
// }
