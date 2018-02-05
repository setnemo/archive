/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:26:19 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/01 14:26:19 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_free(t_mlx *data)
{
	int	i;

	i = 0;
	while (i < data->point[X] * data->point[Y])
		free(data->loc[i++]);
	free(data->loc);
	system("leaks -quiet fdf");
	exit(0);
}

/*
** 53 = ESC							Exit
** 123-126 = up/down/left/right		Move
** 34 = i							Increment Z point
** 31 = o							Decrement Z point
** 35 = p							Coloring peaks
** 8 = c							Coloring figure
** 24 && 27 = + && -				Zoom figure
*/

void	restart(t_mlx *data)
{
	mlx_clear_window(data->mlx, data->win);
	to_window(data);
}

int		deal_key(int k, t_mlx *data)
{
	if (k == 53)
		exit_free(data);
	if (k == 126)
		data->y_loc += 10;
	if (k == 125)
		data->y_loc -= 10;
	if (k == 123)
		data->x_loc -= 10;
	if (k == 124)
		data->x_loc += 10;
	if (k == 34 && data->alt < 5.6)
		data->alt += 0.2;
	if (k == 31)
		data->alt -= 0.2;
	if (k == 35)
		data->peaks = (data->peaks) ? 0 : 1;
	if (k == 8)
		data->colour += (5 * 1 << 16) + 5;
	if (k == 24)
		data->zoom += 0.1;
	if (k == 27 && (data->zoom - 0.1 > 0))
		data->zoom -= 0.1;
	if (k >= 8 && k <= 126)
		restart(data);
	return (k);
}

int		**get_loc(char *str, t_mlx *data, int i, int j)
{
	int		**loc;

	if (!(loc = malloc(sizeof(int *) * (data->point[X] * data->point[Y]))))
		return (NULL);
	while (str[++i])
	{
		if (ft_isdigit(str[i]) || (str[i] == '-' && ft_isdigit(str[i + 1])))
		{
			loc[++j] = malloc(sizeof(int) * 4);
			loc[j][Z] = ft_atoi(str + i);
			if (str[i] == '-')
				i++;
			loc[j][X] = j % data->point[X];
			loc[j][Y] = j / data->point[X];
			loc[j][C] = 0;
			while (ft_isdigit(str[i]))
				i++;
		}
		if (str[i] == ',')
			loc[j][C] = ft_atoi_base(str + ++i, 16);
		while (ft_isdigit(str[i]) || HEXCHAR || HEXSYMB)
			i++;
	}
	return (loc);
}

void	fdf(char *str, t_mlx *data)
{
	data->alt = 1;
	data->height = 0;
	data->peaks = 0;
	data->zoom = 1;
	data->x_loc = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->isize, data->isize, "FDF");
	data->loc = get_loc(str, data, -1, -1);
	free(str);
	to_window(data);
	mlx_key_hook(data->win, deal_key, data);
	mlx_loop(data->mlx);
}
