/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define ATDL ft_atoi(data->line)
#define DL data->line

void				write_input(t_lem *data)
{
	data->temp = ft_strjoin(data->input, data->line);
	ft_strdel(&data->input);
	data->input = ft_strjoin(data->temp, "\n");
	ft_strdel(&data->temp);
	data->countline++;
}

static int			check_links_name(t_lem *data, int i, int flag)
{
	if (*data->line == 0)
		return (1);
	if ((ft_strchr(DL, '-') == NULL) || !(ft_strchr(DL, '-') - DL))
		return (8);
	if (ft_strnequ(DL, ft_strchr(DL, '-') + 1, ft_strchr(DL, '-') - DL))
		return (9);
	while (i < data->how_rooms)
	{
		if (ft_strnequ(data->name_room[i], DL, ft_strchr(DL, '-') - DL))
			flag = 0;
		i++;
	}
	if (flag)
		return (8);
	i = 0;
	flag = 1;
	while (i < data->how_rooms)
	{
		if (ft_strequ(data->name_room[i], ft_strchr(data->line, '-') + 1))
			flag = 0;
		i++;
	}
	if (flag)
		return (8);
	return (0);
}

static void			write_matrix(t_lem *data, int i)
{
	int a;
	int b;

	while (i < data->how_rooms)
	{
		if (ft_strnequ(data->name_room[i], DL, ft_strchr(DL, '-') - DL))
			a = i;
		i++;
	}
	i = 0;
	while (i < data->how_rooms)
	{
		if (ft_strequ(data->name_room[i], ft_strchr(data->line, '-') + 1))
			b = i;
		i++;
	}
	if (a != b)
	{
		data->links[a][b] = 1;
		data->links[b][a] = 1;
	}
	else
	{
		data->links[a][b] = 0;
		data->links[b][a] = 0;
	}
}

void				read_links(t_lem *data)
{
	int flag;

	if (data->read_end)
		manage_error(data, 19);
	if (data->read_start)
		manage_error(data, 18);
	flag = 0;
	write_input(data);
	if (data->line[0] == '#')
	{
		if (ft_strequ(data->line, "##start") || ft_strequ(data->line, "##end"))
			manage_error(data, ft_strequ(data->line, "##start") ? 14 : 15);
	}
	else
	{
		flag = check_links_name(data, 0, 1);
		if (flag)
		{
			break_reading(data, flag);
			data->stop = 0;
		}
		else
			write_matrix(data, 0);
	}
}

static void			check_ants(t_lem *data, int i)
{
	if (data->line[0] == '#')
	{
		if (ft_strequ(data->line, "##start") || ft_strequ(data->line, "##end"))
			manage_error(data, ft_strequ(data->line, "##start") ? 16 : 17);
		ft_strdel(&data->line);
		while (get_next_line(STDIN_FILENO, &data->line) && data->line[0] == '#')
		{
			if (ft_strequ(data->line, "##start") || ft_strequ(data->line, "##end"))
				manage_error(data, ft_strequ(data->line, "##start") ? 16 : 17);
			write_input(data);
			ft_strdel(&data->line);
		}
		write_input(data);
	}
	while (ft_isdigit(data->line[i]))
		i++;
	(data->line[i] == 0) ? data->how_ants = ATDL : manage_error(data, 2);
	if (data->how_ants < 1)
		manage_error(data, 1);
	if (ft_strlen(data->line) > 9)
		manage_error(data, 3);
	ft_strdel(&data->line);
}

void				manage_input(t_lem *data)
{
	if (get_next_line(STDIN_FILENO, &data->line) > 0)
	{
		data->countline = 1;
		data->input = ft_strjoin(data->line, "\n");
		check_ants(data, 0);
		data->how_rooms = 0;
		while (get_next_line(STDIN_FILENO, &data->line) > 0 && data->stop)
		{
			(data->in == 1) ? read_rooms(data) : read_links(data);
			ft_strdel(&data->line);
			if (data->start_count > 1)
				manage_error(data, 10);
			if (data->end_count > 1)
				manage_error(data, 11);
			if (data->stop == 0)
				break ;
		}
		ft_printf("=======>exit input\n");
		//ft_printf("%s", data->input);
		//ft_printf("data->how_rooms:%i\n", data->how_rooms);
		//ft_printf("start :%i\n", data->start_room);
		//ft_printf("end   :%i\n", data->end_room);
		//ft_printf("data->how_ants:%i\n", data->how_ants);
		// read_rooms(data, 0);
		// check_coords(data, 0);
		// data->links = ft_new_int_matrix((size_t)data->how_rooms + 1);
		// check_links_name(data, 0, 1);
		// write_matrix(data, 0);
		// free(data->line);
		// while ((get_next_line(STDIN_FILENO, &data->line)) > 0)
		// {
		// 	check_links_name(data, 0, 1);
		// 	write_matrix(data, 0);
		// 	free(data->line);
		// }
	}
	else
		manage_error(data, 0);
}
