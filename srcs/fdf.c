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

void	quit(t_mlx *data)
{
	int	i;

	i = 0;
	while (i < data->point[X] * data->point[Y])
		free(data->loc[i++]);
	free(data->loc);
	exit(1);
}

// int	deal_key(int key, t_mlx *data)
// {
// 	int	i;

// 	i = 0;
// 	ft_testintstr(key, "key");
// 	if (key == 65307)
// 		quit(data);
// 	if (key == 119)
// 		data->y_loc += 10;
// 	if (key == 97)
// 		data->y_loc -= 10;
// 	if (key == 115)
// 		data->x_loc -= 10;
// 	if (key == 100)
// 		data->x_loc += 10;
// 	if (key == 39 && data->alt < 5.6)
// 		data->alt += 0.2;
// 	if (key == 59)
// 		data->alt -= 0.2;
// 	if (key == 92)
// 		data->peaks = (data->peaks) ? 0 : 1;
// 	if (key == 65288)
// 		data->colour += (5 * 1 << 16) + 5;
// 	if (key == 61)
// 		data->zoom += 0.1;
// 	if (key == 45 && (data->zoom - 0.1 > 0))
// 		data->zoom -= 0.1;
// 	if (key == 91)
// 		data->rot += 1;
// 	if (key == 93)
// 		data->rot -= 1;
// 	if (key == 91 || key == 93 || key == 59 || key == 39 || (key >= 115 && key <= 119) || (key >= 97 && key <= 100) || key == 65288 || key == 92 || key == 61|| key == 45)
// 	{
// 		mlx_clear_window(data->mlx, data->win);
// 		print_toscreen(data);
// 	}
// 	return (key);
// }

int	deal_key(int key, t_mlx *data)
{
	int	i;

	i = 0;
	ft_testintstr(key, "key");
	if (key == 53) //ESC
		quit(data);
	if (key == 126) //up
		data->y_loc += 10;
	if (key == 125) //down
		data->y_loc -= 10;
	if (key == 123) //left
		data->x_loc -= 10;
	if (key == 124) //right
		data->x_loc += 10;
	if (key == 34 && data->alt < 5.6) //i
		data->alt += 0.2;
	if (key == 31) //o
		data->alt -= 0.2;
	if (key == 35) //p
		data->peaks = (data->peaks) ? 0 : 1;
	if (key == 8) //c
		data->colour += (5 * 1 << 16) + 5;
	if (key == 24) //+
		data->zoom += 0.1;
	if (key == 27 && (data->zoom - 0.1 > 0)) //-
		data->zoom -= 0.1;
	if (key == 43) //<
		data->rot += 1;
	if (key == 47) //>
		data->rot -= 1;
	if (key == 43 || key == 47 || key == 31 || key == 34 || (key >= 123 && key <= 126) || key == 8 || key == 35 || key == 24|| key == 27)
	{
		mlx_clear_window(data->mlx, data->win);
		print_toscreen(data);
	}
	return (key);
}

int	**get_loc(char *str, t_mlx *data)
{
	int		i;
	int		**loc;
	int		j;

	j = -1;
	i = -1;
	if(!(loc = malloc(sizeof(int *) * (data->point[X] * data->point[Y]))))
		return (NULL);
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
		{
			loc[++j] = malloc(sizeof(int) * 4);
			loc[j][X] = j % data->point[X];
			loc[j][Y] = j / data->point[X];
			loc[j][Z] = ft_atoi(str + i);
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
	data->rot = 1;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->isize, data->isize, "FDF");
	data->loc = get_loc(str, data);
	free(str);
	print_toscreen(data);
	mlx_key_hook(data->win, deal_key, data);
	mlx_loop(data->mlx);
}
