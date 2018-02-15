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

int		check_flags(t_mlx *data, int argc, char **argv)
{
	if (valid_fdf_map(data, argc, argv))
		;
	else
	{
		ft_printf("%s: ERROR! Bad map!\n", argv[0]);
		return (0);
	}
	if (argv[2] && ft_isdigit(argv[2][0]))
		data->window = ft_atoi(argv[2]) : 1000;
	else
	{
		ft_printf("%s: ERROR! Bad window size!\n", argv[0]);
		return (0);
	}
	if (argv[3] && ft_check_hex(argv[3]))
		data->fill = ft_atoi(argv[2]) : 1000;
	else
	{
		ft_printf("%s: ERROR! Bad fill color! Use HEX digits without '0x'\n", argv[0]);
		return (0);
	}
}

int     main(int argc, char **argv)
{
	t_mlx	*data;

	data = NULL;
	if (argc > 1)
	{
		data = (t_mlx*)malloc(sizeof(t_mlx));
		ft_bzero(t_mlx, sizeof(t_mlx));
		if (!(check_flags(data, argc, argv)))
			exit(1);
	}
	else
	{
		ft_printf("usage: %s: [map_file_path] [size_window] [color]", argv[0]);
		exit(1);
	}
	return (0);
}