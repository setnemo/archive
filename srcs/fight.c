/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 12:11:36 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/07 12:11:36 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		check_bit(t_fill *g, int a, int b)
{
	int ret;

	ret = 0;
	if (a - g->bit_size[0] + 1 > 0)
	{
		;
		// if (g->matrix[a - 1][b] == 0 && ++ret)
		// 	g->matrix[a - 1][b] = (*i) + 1;
		// if (b + 1 < g->map_size[1] && g->matrix[a - 1][b + 1] == 0 && ++ret)
		// 	g->matrix[a - 1][b + 1] = (*i) + 1;
		// if (b - 1 > 0 && g->matrix[a - 1][b - 1] == 0  && ++ret)
		// 	g->matrix[a - 1][b - 1] = (*i) + 1;
	}
	if (a + g->bit_size[0] - 1 < g->map_size[0])
	{
		;
		// if (g->matrix[a + 1][b] == 0 && ++ret)
		// 	g->matrix[a + 1][b] = (*i) + 1;
		// if (b + 1 < g->map_size[1] && g->matrix[a + 1][b + 1] == 0 && ++ret)
		// 	g->matrix[a + 1][b + 1] = (*i) + 1;
		// if (b - 1 > 0 && g->matrix[a + 1][b - 1] == 0 && ++ret)
		// 	g->matrix[a + 1][b - 1] = (*i) + 1;
	}
	if (b - g->bit_size[1] + 1 > 0)
		;
		// g->matrix[a][b - 1] = (*i) + 1;
	if (b + g->bit_size[1] - 1 < g->map_size[1])
		;
		// g->matrix[a][b + 1] = (*i) + 1;	
}

void		find_spot(t_fill *g)
{
	int a;
	int b;
	size_t temp;

	a = 0;
	temp = g->xo * g->map_size[1] * g->map_size[0];
	while (a < g->map_size[0])
	{
		b = 0;
		while (b < g->map_size[1])
		{		
			if (g->matrix[a][b] == temp)
				check_bit(g, a, b);
			b++;
		}
		a++;
	}
}

void		matrix_map(t_fill *g)
{
	int a;
	int b;

	a = 0;
	g->matrix = (size_t**)malloc(sizeof(size_t*) * g->map_size[0]);
	while (a < g->map_size[0])
	{
		g->matrix[a] = (size_t*)malloc(sizeof(size_t) * g->map_size[1]);
		b = 0;
		while (b < g->map_size[1])
		{
			if (g->map[a][b] == '.')
				g->matrix[a][b] = 0;
			else if (g->map[a][b] == g->xo)
				g->matrix[a][b] = g->xo * g->map_size[1] * g->map_size[0];
			else if (g->map[a][b] == g->enemy)
				g->matrix[a][b] = g->enemy * g->map_size[1] * g->map_size[0];
			b++;
		}
		a++;
	}
}

int			fill_point(t_fill *g, size_t *i, int a, int b)
{
	int ret;

	ret = 0;
	if (a - 1 > 0 && a - g->map_size[0])
	{
		if (g->matrix[a - 1][b] == 0 && ++ret)
			g->matrix[a - 1][b] = (*i) + 1;
		if (b + 1 < g->map_size[1] && g->matrix[a - 1][b + 1] == 0 && ++ret)
			g->matrix[a - 1][b + 1] = (*i) + 1;
		if (b - 1 > 0 && g->matrix[a - 1][b - 1] == 0  && ++ret)
			g->matrix[a - 1][b - 1] = (*i) + 1;
	}
	if (a + 1 < g->map_size[0])
	{
		if (g->matrix[a + 1][b] == 0 && ++ret)
			g->matrix[a + 1][b] = (*i) + 1;
		if (b + 1 < g->map_size[1] && g->matrix[a + 1][b + 1] == 0 && ++ret)
			g->matrix[a + 1][b + 1] = (*i) + 1;
		if (b - 1 > 0 && g->matrix[a + 1][b - 1] == 0 && ++ret)
			g->matrix[a + 1][b - 1] = (*i) + 1;
	}
	if (b - 1 > 0 && g->matrix[a][b - 1] == 0 && ++ret)
		g->matrix[a][b - 1] = (*i) + 1;
	if (b + 1 < g->map_size[1] && g->matrix[a][b + 1] == 0 && ++ret)
		g->matrix[a][b + 1] = (*i) + 1;
	return (ret);
}

void		matrix_fill_two(t_fill *g, size_t *i, char *flag)
{
	int a;
	int b;

	a = 0;
	*flag = 0;
	while (a < g->map_size[0])
	{
		b = 0;
		while (b < g->map_size[1])
		{		
			if (g->matrix[a][b] == *i)
				if (fill_point(g, i, a, b))
					*flag = 1;
			b++;
		}
		a++;
	}
}

void		matrix_fill_one(t_fill *g, size_t *i)
{
	int a;
	int b;

	a = 0;
	while (a < g->map_size[0])
	{
		b = 0;
		while (b < g->map_size[1])
		{		
			if (g->map[a][b] == g->enemy)
				fill_point(g, i, a, b);
			b++;
		}
		a++;
	}
}

void		spot_loc(t_fill *g)
{
	char	flag;
	size_t	i;

	flag = 1;
	i = 1;
	matrix_map(g);
	matrix_fill_one(g, &i);
	i++;
	while (flag)
	{
		matrix_fill_two(g, &i, &flag);
		i++;
	}
	dprintf(g->fd, "-----1-----\n");
	for (int i = 0; i < g->map_size[0]; ++i)
	{
		for (int j = 0; j < g->map_size[1]; ++j)
			dprintf(g->fd, "%zu ", g->matrix[i][j]);
		dprintf(g->fd, "\n");
	}
	dprintf(g->fd, "-----2------\n");
	find_spot(g);
}

void		wait_enemy(t_fill *g)
{
	char	*line;

	get_next_line(STDIN_FILENO, &line);
	line += 6;
	g->wait = ft_atoi(line) + 1;
	// ft_strdel(&line);
	while (g->wait--)
	{
		get_next_line(STDIN_FILENO, &line);
		// ft_strdel(&line);
	}
}
