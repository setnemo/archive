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
// #define XY data->xy_rooms
// #define DL data->line

// static void			check_coords(t_lem *data, int i)
// {
// 	int j;

// 	while (i + 1 < data->how_rooms)
// 	{
// 		j = 0;
// 		while (j + i + 1 < data->how_rooms)
// 		{
// 			if (XY[i][0] == XY[i + 1 + j][0] && XY[i][1] == XY[i + 1 + j][1])
// 			{
// 				manage_error(data, 7);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void			check_links_name(t_lem *data, int i, int flag)
// {
// 	if ((ft_strchr(DL, '-') == NULL) || !(ft_strchr(DL, '-') - DL))
// 		manage_error(data, 8);
// 	if (ft_strnequ(DL, ft_strchr(DL, '-') + 1, ft_strchr(DL, '-') - DL))
// 		manage_error(data, 9);
// 	while (i < data->how_rooms)
// 	{
// 		if (ft_strnequ(data->name_room[i], DL, ft_strchr(DL, '-') - DL))
// 			flag = 0;
// 		i++;
// 	}
// 	if (flag)
// 		manage_error(data, 8);
// 	i = 0;
// 	flag = 1;
// 	while (i < data->how_rooms)
// 	{
// 		if (ft_strequ(data->name_room[i], ft_strchr(data->line, '-') + 1))
// 			flag = 0;
// 		i++;
// 	}
// 	if (flag)
// 		manage_error(data, 8);
// }

// static void			write_matrix(t_lem *data, int i)
// {
// 	int a;
// 	int b;

// 	while (i < data->how_rooms)
// 	{
// 		if (ft_strnequ(data->name_room[i], DL, ft_strchr(DL, '-') - DL))
// 			a = i;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->how_rooms)
// 	{
// 		if (ft_strequ(data->name_room[i], ft_strchr(data->line, '-') + 1))
// 			b = i;
// 		i++;
// 	}
// 	data->links[a][b] = 1;
// 	data->links[b][a] = 0;
// }

// static void			check_ants(t_lem *data, int i)
// {
// 	while (data->line[0] == '#')
// 	{
// 		ft_strdel(&data->line);
// 		get_next_line(STDIN_FILENO, &data->line);
// 	}
// 	while (ft_isdigit(data->line[i]))
// 		i++;
// 	if (data->line[i] == 0)
// 		data->how_ants = ft_atoi(data->line);
// 	else
// 		manage_error(data, 2);
// 	ft_strdel(&data->line);
// 	if (data->how_ants < 1)
// 		manage_error(data, 1);
// 	if (data->how_ants > 2147483647)
// 		manage_error(data, 3);
// }


























void				manage_input(t_lem *data)
{
	if (get_next_line(STDIN_FILENO, &data->line) > 0)
	{
		// check_ants(data, 0);
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
