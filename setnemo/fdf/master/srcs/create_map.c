/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#define NORMCRM1 data->map[*a][data->iter]
#define NORMCRM2 data->map[*a][data->iter + 1]

static void		write_dot1(t_map *lines, int *a, int *count, t_mlx *data)
{
	lines->py = *a;
	lines->px = *count;
	lines->pz = (ft_atoi(&data->map[*a][data->iter])) * 10;
	if (data->map[*a][data->iter] == '-')
		data->iter++;
	while (data->map[*a][data->iter] && ft_isdigit(data->map[*a][data->iter]))
		data->iter++;
	(*count)++;
}

static void		create_lines(t_mlx *data, t_map *lines, int *a, int *count)
{
	while (NORMCRM1)
	{
		if (ft_isdigit(NORMCRM1) || (NORMCRM1 == '-' && ft_isdigit(NORMCRM2)))
			write_dot1(lines, a, count, data);
		if (data->map[*a][data->iter] == ',')
		{
			data->iter += 2;
			lines->pc = ft_hex_to_ul(&data->map[*a][data->iter]);
			while (NORMCRM1 && ft_check_hex_char(NORMCRM1))
				data->iter++;
		}
		while (NORMCRM1 && NORMCRM1 == 32)
			data->iter++;
		data->iter--;
		if (data->map[*a][data->iter] != 0)
			data->iter++;
		if (*count < data->how_x)
		{
			lines->next = (t_map*)malloc(sizeof(t_map));
			lines = lines->next;
			ft_bzero(lines, sizeof(t_map));
		}
		else
			lines->next = NULL;
	}
}

static t_map	*while_lines(t_map *lines)
{
	while (lines)
	{
		if (lines->next)
			lines = lines->next;
		else
			break ;
	}
	return (lines);
}

int				create_fdf_map(t_mlx *data, int a, int count)
{
	t_map	*lines;

	data->line = (t_map*)malloc(sizeof(t_map));
	lines = data->line;
	ft_bzero(data->line, sizeof(t_map));
	while (data->map[a])
	{
		count = 0;
		if (a < data->how_y)
		{
			data->iter = 0;
			create_lines(data, lines, &a, &count);
			lines = while_lines(lines);
			a++;
			if (a < data->how_y)
			{
				lines->next = (t_map*)malloc(sizeof(t_map));
				lines = lines->next;
				ft_bzero(lines, sizeof(t_map));
			}
			else
				lines->next = NULL;
		}
	}
	return (0);
}
