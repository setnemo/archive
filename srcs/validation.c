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
#define FCH ft_strchr

// #define XY data->xy_rooms
// #define DL data->line

static int			check_coords_digits(char *line)
{
	int i;
	int sp;

	line = ft_strchr(line, 32);
	line++;
	sp = 1;
	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			i++;
		else if (sp && line[i] == 32)
			i++;
		else if (line[i] && sp == 0)
			return (0);
		else
			return (1);
	}
	return (0);
}

static void			free_validcoord(t_lem *data)
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

static int			valid_coords(t_lem *data, int i, int j, int *a)
{
	int		b[2];

	while (i < j)
	{
		if (data->validcoord[i] == NULL)
			break ;
		if (ft_strequ(data->validcoord[i], data->line) ||
			data->validcoord[i][0] == '#')
			i++;
		else
		{
			b[0] = ft_atoi(ft_strchr(data->validcoord[i], 32));
			b[1] = ft_atoi(ft_strrchr(data->validcoord[i], 32));
			if (a[0] == b[0] && a[1] == b[1])
				return (1);
			i++;
		}
	}
	return (0);
}

static int			check_coords(t_lem *data, int i, int j)
{
	char	*p;
	int		a[2];

	i = data->startroomline - 1;
	p = data->input;
	a[0] = ft_atoi(ft_strchr(data->line, 32));
	a[1] = ft_atoi(ft_strrchr(data->line, 32));
	while (i)
	{
		if (*p == 10)
			i--;
		p++;
	}
	i = 0;
	j = ft_count_to_null((void**)p, 0) + 1;
	data->validcoord = ft_strsplit(p, 10);
	if (valid_coords(data, i, j, a))
		return (1);
	free_validcoord(data);
	return (0);
}

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

static void			write_input(t_lem *data)
{
	data->temp = ft_strjoin(data->input, data->line);
	ft_strdel(&data->input);
	data->input = ft_strjoin(data->temp, "\n");
	ft_strdel(&data->temp);
	data->countline++;
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

void				read_links(t_lem *data)
{
	write_input(data);
}

static void			manage_start_end(t_lem *data)
{
	data->bound = ft_strequ(data->line, "##start") ? 1 : 2;
	if (data->bound == 1)
		data->start_count++;
	else if (data->bound == 2)
		data->end_count++;
}

static void			manage_room(t_lem *data)
{
	if (data->bound == 1)
		data->start_room = data->how_rooms;
	else if (data->bound == 2)
		data->end_room = data->how_rooms;
	data->how_rooms++;
	data->bound = 0;
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

// ft_printf("ble\n");

void				manage_input(t_lem *data)
{
	if (get_next_line(STDIN_FILENO, &data->line) > 0)
	{
		data->countline = 1;
		data->input = ft_strjoin(data->line, "\n");
		check_ants(data, 0);
		data->rooms = ft_strnew(0);
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
