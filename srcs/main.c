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
#define ARGSP [map_path] [size_window] [color]

static int		valid_fdf_map(t_mlx *data, int argc, char **argv)
{
	char	*line;
	char	*temp2;
	char	*temp1;

	data->ret = 0;
	if ((data->fd = (argc > 1) ? open(argv[1], O_RDONLY) : 0) < 1)
	{
		ft_printf("%s: ERROR! Bad file descriptor!\n", argv[0]);
		exit(1);
	}
	while ((data->ret = get_next_line(data->fd, &line)))
	{
		temp2 = ft_strjoin(line, "\n");
		ft_strdel(&line);
		temp1 = ft_strjoin(data->str, temp2);
		ft_strdel(&temp2);
		ft_strdel(&data->str);
		data->str = ft_strdup(temp1);
		ft_strdel(&temp1);
	}
	if (data->ret < 0)
		return (0);
	if (check_fdf_map(data))
		return (0);
	return (create_fdf_map(data));
}

static int		check_argc2(t_mlx *data, char **argv)
{
	if (argv[2] != NULL && ft_isdigit(argv[2][0]) &&
		(ft_atoi(argv[2]) > 299 && ft_atoi(argv[2]) < 1401))
		data->window = ft_atoi(argv[2]);
	else
	{
		free_data(data);
		ft_printf("%s: ERROR! Bad window size!\n", argv[0]);
		return (0);
	}
	return (1);
}

static int		check_argc3(t_mlx *data, char **argv)
{
	if (argv[3] != NULL && argv[3][0] == '0' &&
		(argv[3][1] == 'x' || argv[3][1] == 'X') &&
		ft_check_hex(&argv[3][2]) && (argv[3][8] == 0 || argv[3][8] == 32))
		data->fill = ft_hex_to_ul(&argv[3][2]);
	else
	{
		free_data(data);
		ft_printf("%s: ERROR! Bad fill color! Use '0x' or '0X' hex\n", argv[0]);
		return (0);
	}
	return (1);
}

static int		check_flags(t_mlx *data, int argc, char **argv)
{
	if ((valid_fdf_map(data, argc, argv)))
	{
		free_data(data);
		ft_printf("%s: ERROR! Bad map!\n", argv[0]);
		return (0);
	}
	if (argc > 2)
	{
		if (check_argc2(data, argv) == 0)
			return (0);
	}
	if (argc > 3)
	{
		if (check_argc3(data, argv) == 0)
			return (0);
	}
	if (argc > 4)
	{
		free_data(data);
		ft_printf("%s: ERROR! Too many arguments!\n", argv[0]);
		system("leaks -quiet fdf");
		return (0);
	}
	return (1);
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
		data->str = NULL;
		data->map = NULL;
		data->str = ft_strnew(0);
		data->fill = 0xFFFFFF;
		if ((check_flags(data, argc, argv)))
			exit(1);
	}
	else
	{
		ft_printf("usage: %s: ARGSP\n", argv[0]);
		exit(1);
	}
	return (0);
}
