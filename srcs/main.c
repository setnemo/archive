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

int		check_fdf_map(t_mlx *data)
{
	int a;

	a = 0;
	while (data->map[a])
	{
		if (check_fdf_str(data, a))
		a++;
	}
	return (0);
}

int		valid_fdf_map(t_mlx *data, int argc, char **argv)
{
	int		ret;
	char	*temp;

	ret = 0;
	if (!(data->fd = (argc > 1) ? open(argv[1], O_RDONLY) : 0))
	{
		ft_printf("%s: ERROR! Bad file descriptor!\n", argv[0]);
		exit(1);
	}
	while ((ret = get_next_line(data->fd, &temp)))
	{
		data->str = ft_strjoin(temp, "\n");
		ft_strdel(&temp);
	}
	if (ret < 0)
		return (0);
	data->map = ft_strsplit(data->str, 10);
	if (check_fdf_map(data))
		return (0);
	return (create_fdf_map(data));
}

int		check_flags(t_mlx *data, int argc, char **argv)
{
	if (argv[2] && ft_isdigit(argv[2][0]) &&
		(ft_atoi(argv[2]) > 299 && ft_atoi(argv[2]) < 1401))
		data->window = ft_atoi(argv[2]);
	else
	{
		free(data);
		ft_printf("%s: ERROR! Bad window size!\n", argv[0]);
		return (0);
	}
	if (argv[3] && ft_check_hex(argv[3]))
		data->fill = ft_hex_to_ul(argv[3]);
	else
	{
		free(data);
		ft_printf("%s: ERROR! Bad fill color! Use HEX digits without '0x'\n", argv[0]);
		return (0);
	}
	if (!(valid_fdf_map(data, argc, argv)))
	{
		free_data(data);
		ft_printf("%s: ERROR! Bad map!\n", argv[0]);
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
		ft_bzero(data, sizeof(t_mlx));
		data->window = 1000;
		data->fill = ft_hex_to_ul("FFFFFF");
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
