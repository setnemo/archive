/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ARGSP "[map_path] [size_window] [color]"

static void		free_map(t_map *lines)
{
	t_map *temp;

	while (lines)
	{
		if (lines->next)
		{
			temp = lines;
			lines = lines->next;
			free(temp);
		}
		else
		{
			free(lines);
			lines = NULL;
		}
	}
	
}
void			free_data(t_mlx *data, int a)
{
	if (data->str)
		ft_strdel(&data->str);
	if (data->map)
	{
		while (data->map[a])
		{
			ft_strdel(&data->map[a]);
			a++;
		}
		free(data->map);
	}
	if (data->line)
		free_map(data->line);
	free(data);
}

int				main(int argc, char **argv)
{
	t_mlx	*data;

	data = NULL;
	if (argc > 1)
	{
		data = (t_mlx*)malloc(sizeof(t_mlx));
		ft_bzero(data, sizeof(t_mlx));
		data->window = 1000;
		data->map = NULL;
		data->line = NULL;
		data->str = ft_strnew(0);
		data->fill = 0xFFFFFF;
		if ((check_flags(data, argc, argv)))
			exit(1);
	}
	else
	{
		ft_printf("usage: %s: %s\n", argv[0], ARGSP);
		exit(1);
	}
	return (0);
}
