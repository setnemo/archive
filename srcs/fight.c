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

void		search_location(t_fill *game, char *str, char x, int i)
{
	int b;

	b = 0;
	while (b < game->map_size[1])
	{
		if (str[b] == x)
			if (game->loc[i] == 0 && game->loc[i] =< a)
				game->loc[i] = a;
		if (str[b] == x)
			if (game->loc[i + 1] == 0 && game->loc[i + 1] =< b)
				game->loc[i + 1] = b;
		if (str[b] == x)
			if (game->loc[i + 2] < a)
				game->loc[i + 2] = a;
		if (str[b] == x)
			if (game->loc[i + 3] < b)
				game->loc[i + 3] = b;
		if (str[b] == x)
			if (game->loc[i] == 0 && game->loc[i] =< a)
				game->loc[i] = a;
		if (str[b] == x)
			if (game->loc[i + 1] == 0 && game->loc[i + 1] =< b)
				game->loc[i + 1] = b;
		if (str[b] == x)
			if (game->loc[i + 2] < a)
				game->loc[i + 2] = a;
		if (str[b] == x)
			if (game->loc[i + 3] < b)
				game->loc[i + 3] = b;
		b++;
	}
}

void		search_loc(t_fill *game, char x, int i)
{
	int a;

	a = 0;
	while (a < game->map_size[0])
	{
		search_location(game, game->map[a], x, i);
		a++;
	}
}

void		enemy_dist(t_fill *game)
{
	ft_bzero(&game->loc, sizeof(int) * 16);
	search_loc(game, game->xo, 0);
	search_loc(game, game->enemy, 8);

}

void		spot_loc(t_fill *game)
{
	enemy_dist(game);

}

void		wait_enemy(t_fill *game)
{
	char	*line;

	get_next_line(STDIN_FILENO, &line);
	line += 6;
	game->wait = ft_atoi(line) + 1;
	ft_strdel(&line);
	while (game->wait--)
	{
		get_next_line(STDIN_FILENO, &line);
		ft_strdel(&line);
	}
}
