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

static void		write_lines(t_map *lines, int a, int count, char *str)
{
	lines->px1 = a;
	lines->py1 = count;
	lines->pz = ft_atoi(str);
}
static void		create_lines(t_mlx *data, t_map *lines, int a, int count)
{
	int	i;

	i = 0;
	while (data->map[a][i])
	{
		if (ft_isdigit(data->map[a][i]) || (data->map[a][i] == '-' && ft_isdigit(data->map[a][i + 1])))
		{
			write_lines(lines, a, count, &data->map[a][i]);
			count++;
			if (data->map[a][i] == '-')
				i++;
			while (data->map[a][i] && ft_isdigit(data->map[a][i]))
				i++;
		}
		if (data->map[a][i] == ',')
		{
			i += 2;
			lines->pc = ft_hex_to_ul(&data->map[a][i]);
			while (data->map[a][i] && ft_check_hex_char(data->map[a][i]))
				i++;
		}
		if (count <= data->how_y - 1)
		{
			lines->next = (t_map*)malloc(sizeof(t_map));
			lines = lines->next;
			ft_bzero(lines, sizeof(t_map));
		}
		else
			lines->next = NULL;
		i++;
	}
}

int				create_fdf_map(t_mlx *data)
{
	int		a;
	t_map	*lines;

	a = 0;
	data->line = (t_map*)malloc(sizeof(t_map));
	lines = data->line;
	ft_bzero(lines, sizeof(t_map));
	while (data->map[a])
	{
		if (a <= data->how_x - 1)
		{
			create_lines(data, lines, a, 0);
			while (lines)
			{
				if (lines->next)
					lines = lines->next;
				else
					break ;
			}
			if (a < data->how_x - 1)
			{
				lines->next = (t_map*)malloc(sizeof(t_map));
				lines = lines->next;
				ft_bzero(lines, sizeof(t_map));
			}
		}
		else
			lines->next = NULL;
		a++;
	}
	// lines = data->line;
	// int i = 1;
	// while (lines)
	// {
	// 	ft_printf(":%i:lines->px1 = '%i'\n",i, lines->px1);
	// 	ft_printf(":%i:lines->py1 = '%i'\n",i, lines->py1);
	// 	ft_printf(":%i:lines->pz = '%i'\n", i,lines->pz);
	// 	ft_printf(":%i:lines->pc = '%d'\n", i,lines->pc);
	// 	lines = lines->next;
	// 	i++;
	// }
	// ft_printf("::::data->how_x = '%i'\n", data->how_x);
	// ft_printf("::::data->how_y = '%i'\n", data->how_y);
	// for (int i = 0; i < 10; i++)
	// 	ft_printf("%s\n", data->map[i]);
	return (0);
}
