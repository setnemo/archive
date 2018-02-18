/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define CHKAR1 argv[3][0] == '0' && (argv[3][1] == 'x' || argv[3][1] == 'X')
#define CHKAR2 (argv[3][8] == 0 || argv[3][8] == 32)

static int		check_fdf_str(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1])))
		{
			if (str[i] == '-')
				i++;
			count++;
			while (str[i] && ft_isdigit(str[i]) )
				i++;
		}
		if (str[i] == ',')
		{
			i += 2;
			while (str[i] && ft_check_hex_char(str[i]))
				i++;
		}
		if (str[i] != 0)
			i++;
	}
	return (count);
}

static int		check_fdf_map(t_mlx *data)
{
	int a;
	int count;
	int nextcount;

	a = 0;
	count = 0;
	data->map = ft_strsplit(data->str, 10);
	nextcount = check_fdf_str(data->map[a]);
	while (data->map[a])
	{
		count = nextcount;
		nextcount = check_fdf_str(data->map[a]);
		if (count != nextcount)
			return (1);
		a++;
	}
	data->how_x = a;
	data->how_y = count;
	return (0);
}

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
	while ((data->ret = get_next_line(data->fd, &line)) > 0)
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
		return (1);
	if (check_fdf_map(data))
		return (1);
	return (create_fdf_map(data));
}

static int		check_argc(t_mlx *data, char **argv, int flag)
{
	if (flag == 2)
	{
		if (argv[2] != NULL && ft_isdigit(argv[2][0]) &&
			(ft_atoi(argv[2]) > 299 && ft_atoi(argv[2]) < 1401))
			data->window = ft_atoi(argv[2]);
		else
		{
			free_data(data, 0);
			ft_printf("%s: ERROR! Bad window size!\n", argv[0]);
			return (0);
		}
	}
	else
	{
		if (argv[3] != NULL && CHKAR1 && ft_check_hex(&argv[3][2]) && CHKAR2)
			data->fill = ft_hex_to_ul(&argv[3][2]);
		else
		{
			free_data(data, 0);
			ft_printf("%s: ERROR! Bad fill color! '0x'/'0X' hex\n", argv[0]);
			return (0);
		}
	}
	return (1);
}

int				check_flags(t_mlx *data, int argc, char **argv)
{
	if ((valid_fdf_map(data, argc, argv)))
	{
		free_data(data, 0);
		ft_printf("%s: ERROR! Bad map!\n", argv[0]);
		return (0);
	}
	if (argc > 2)
		if (check_argc(data, argv, 2) == 0)
			return (0);
	if (argc > 3)
		if (check_argc(data, argv, 3) == 0)
			return (0);
	if (argc > 4)
	{
		free_data(data, 0);
		ft_printf("%s: ERROR! Too many arguments!\n", argv[0]);
		system("leaks -quiet fdf");
		return (0);
	}
	return (1);
}
