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

static void		write_dot2(t_map *lines, int *a, int *count, t_mlx *data)
{
	if (*a + 1 < data->how_x)
	{
		lines->px1 = *a + 1;
		lines->py1 = *count;
	}
	else
	{
		lines->px1 = *a;
		lines->py1 = *count;
	}
	if (*count + 1 < data->how_y)
	{
		lines->px2 = *a;
		lines->py2 = *count + 1;
	}
	else
	{
		lines->px2 = *a;
		lines->py2 = *count;
	}
		
	// if (a == 0 && *count == 0)
	// {
	// 	lines->flag2 = 1;
	// 	lines->px2 = a + 1;
	// 	lines->py2 = *count;
	// }
}

static void		write_dot1(t_map *lines, int *a, int *count, t_mlx *data)
{
	lines->px = *a;
	lines->py = *count;
	lines->pz = (ft_atoi(&data->map[*a][data->iter]));
	if (data->map[*a][data->iter] == '-')
		data->iter++;
	while (data->map[*a][data->iter] && ft_isdigit(data->map[*a][data->iter]))
		data->iter++;
}

static void		create_lines(t_mlx *data, t_map *lines, int *a, int *count)
{
	while (data->map[*a][data->iter])
	{
		if (ft_isdigit(data->map[*a][data->iter]) || (data->map[*a][data->iter] == '-' && ft_isdigit(data->map[*a][data->iter + 1])))
			write_dot1(lines, a, count, data);
		write_dot2(lines, a, count, data);
		(*count)++;
		if (data->map[*a][data->iter] == ',')
		{
			data->iter += 2;
			lines->pc = ft_hex_to_ul(&data->map[*a][data->iter]);
			while (data->map[*a][data->iter] && ft_check_hex_char(data->map[*a][data->iter]))
				data->iter++;
		}
		while (data->map[*a][data->iter] && data->map[*a][data->iter] == 32)
			data->iter++;
		data->iter--;
		if (*count < data->how_y)
		{
			lines->next = (t_map*)malloc(sizeof(t_map));
			lines = lines->next;
			ft_bzero(lines, sizeof(t_map));
		}
		else
			lines->next = NULL;
		if (data->map[*a][data->iter] != 0)
			data->iter++;
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

int				create_fdf_map(t_mlx *data, int a)
{
	t_map	*lines;
	int		count;

	data->line = (t_map*)malloc(sizeof(t_map));
	lines = data->line;
	ft_bzero(data->line, sizeof(t_map));
	while (data->map[a])
	{
		count = 0;
		if (a < data->how_x)
		{
			data->iter = 0;
			create_lines(data, lines, &a, &count);
			lines = while_lines(lines);
			a++;
			if (a < data->how_x)
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
	// lines = data->line;
	// int i = 1;
	// while (lines)
	// {
	// 	ft_printf(":ШШШ:lines->px lines->py lines->px1 lines->py1 lines->px2 lines->py2 lines->pz lines->pc\n");
	// 	printf(" %i         %f         %f       %f         %f         %f          %f        %f        %lu\n",i, lines->px, lines->py,lines->px1, lines->py1,lines->px2, lines->py2,lines->pz,lines->pc);
	// 	if (lines->next)
	// 		lines = lines->next;
	// 	else
	// 		break ;
	// 	i++;
	// }
	// free_data(data, 0);

	// ft_printf("::::data->how_x = '%i'\n", data->how_x);
	// ft_printf("::::data->how_y = '%i'\n", data->how_y);
	// for (int i = 0; i < 10; i++)
	// 	ft_printf("%s\n", data->map[i]);

	// while (lines)
	// {
	// 	ft_printf(":%i:lines->px1 = '%i'\n",i, lines->px1);
	// 	ft_printf(":%i:lines->py1 = '%i'\n",i, lines->py1);
	// 	ft_printf(":%i:lines->pz = '%i'\n", i,lines->pz);
	// 	ft_printf(":%i:lines->pc = '%d'\n", i,lines->pc);
	// 	lines = lines->next;
	// 	i++;
	// }