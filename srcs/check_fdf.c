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

static int		check_fdf_str(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1])))
		{
			if (str[i] == '-')
				i++;
			count++;
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
		if (str[i] == ',')
		{
			i += 2;
			while (str[i] && ft_check_hex_char(str[i]))
				i++;
		}
		i++;
	}
	return (count);
}

void	free_data(t_mlx *data)
{
	int a;

	a = 0;
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
	free(data);
}

int		check_fdf_map(t_mlx *data)
{
	int a;
	int count;
	int nextcount;

	a = 0;
	data->map = ft_strsplit(data->str, 10);
	nextcount = check_fdf_str(data->map[a]);
	while (data->map[a])
	{
		count = nextcount;
		nextcount = check_fdf_str(data->map[a]);
		if (count != nextcount)
			return (0);
		a++;
	}
	return (1);
}

int		create_fdf_map(t_mlx *data)
{
	int a;
	int b;
	int c;

	a = 0;
	c = 0;
	while (data->map[a])
	{
		b = 0;
		while (data->map[a][b])
		{
			matrix[c][X] = a;
			matrix[c][Y] = d;
			matrix[c][Z] = ft_atoi(data->map[a][b]);
			matrix[c][C] = 
			b += ;
			c++;
		}
		a++;
	}
	// for (int i = 0; i < 22; i++)
	// 	ft_printf("%s\n", data->map[i]);
	return (0);
}
