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

void				write_input(t_lem *data)
{
	data->temp = ft_strjoin(data->input, data->line);
	ft_strdel(&data->input);
	data->input = ft_strjoin(data->temp, "\n");
	ft_strdel(&data->temp);
	data->countline++;
}

void				read_links(t_lem *data)
{
	write_input(data);
}

static void			check_ants(t_lem *data, int i)
{
	if (data->line[0] == '#')
	{
		ft_strdel(&data->line);
		while (get_next_line(STDIN_FILENO, &data->line) && data->line[0] == '#')
		{
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
	if (data->how_ants > 2147483647)
		manage_error(data, 3);
	ft_strdel(&data->line);
}
// ft_printf("ble\n");

void				manage_input(t_lem *data)
{
	if (get_next_line(STDIN_FILENO, &data->line) > 0)
	{
		data->countline = 1;
		data->input = ft_strjoin(data->line, "\n");
		check_ants(data, 0);
		data->how_rooms = 0;
		while (get_next_line(STDIN_FILENO, &data->line))
		{
			(data->in == 1) ? read_rooms(data) : read_links(data);
			ft_strdel(&data->line);
			if (data->start_count > 1)
				manage_error(data, 10);
			if (data->end_count > 1)
				manage_error(data, 11);
		}
		ft_printf("%s", data->input);
		ft_printf("start count line:%i\n", data->startroomline);
		ft_printf("end   rooms line:%i\n", data->endroomline);
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
