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
			// ft_printf("temp(lines)\n");
			free(temp);
		}
		else
		{
			// ft_printf("lines\n");
			free(lines);
			lines = NULL;
		}
	}
}

void			free_data(t_mlx *data, int a)
{
	// ft_printf("data->str\n");
	if (data->str)
		ft_strdel(&data->str);
	// ft_printf("data->map\n");
	if (data->map)
	{
		while (data->map[a])
		{
			// ft_printf("data->map[%i]\n", a);
			ft_strdel(&data->map[a]);
			a++;
		}
		// ft_printf("data->map()\n");
		free(data->map);
	}
	// ft_printf("data->line\n");
	if (data->line)
		free_map(data->line);
	// ft_printf("data()\n");
	free(data);
}

void			legend(t_mlx *data)
{
	mlx_string_put(data->mlx, data->win, 50, 35, 0xfbba00, "FDF @apakhomo");
	mlx_string_put(data->mlx, data->win, 200, 35, 0xfbba00, "MOVE");
	mlx_string_put(data->mlx, data->win, 400, 35, 0xfbba00, "ZOOM");
	mlx_string_put(data->mlx, data->win, 600, 35, 0xfbba00, "ROTATE");
	mlx_string_put(data->mlx, data->win, 800, 35, 0xfbba00, "EXIT");
	mlx_string_put(data->mlx, data->win, 300, 100, 0x00CC00, "test2");
	mlx_string_put(data->mlx, data->win, 400, 150, 0x00CC00, "test3");
	mlx_string_put(data->mlx, data->win, 500, 200, 0x00CC00, "test4");
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
		data->zoomnew = 1;
		if ((check_flags(data, argc, argv)))
		{
			system("leaks -quiet fdf");
			exit(1);
		}
	}
	else
	{
		ft_printf("usage: %s: %s\n", argv[0], ARGSP);
		exit(1);
	}
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->window, data->window, "FDF");
	legend(data);
	scale(data, 0);
	start_fdf(data);
	mlx_key_hook(data->win, deal_key, data);
	mlx_loop(data->mlx);
	free_data(data, 0);
	system("leaks -quiet fdf");
	return (0);
}
