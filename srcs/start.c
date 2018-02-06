/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	start_fight(t_fill *game)
{
	while (1)
	{
		read_bit(game);
		spot_loc(game);
		wait_enemy(game);
		read_new_map(game);
		check_end(game);
	}
}

void	read_map(t_fill *game)
{
	int		row;
	int		col;
	int		a;
	char	*line;

	row = game->map_size[0];
	col = game->map_size[1];
	game->map = (char**)malloc((sizeof(char*) * row) + 1);
	game->map[row] = NULL;
	a = 0;
	get_next_line(STDIN_FILENO, &line);
	ft_strdel(&line);
	while (a < row)
	{
		get_next_line(STDIN_FILENO, &line);
		game->map[a] = ft_strdup(line + 4);
		ft_strdel(&line);
		a++;
	}
	//ft_prcharr(game->map, row);
}

void	start_play(t_fill *game)
{
	read_map(game);
	if (game->xo == 'O')
	{
		read_bit(game);
		spot_loc(game);
		wait_enemy(game);
		read_new_map(game);
		check_end(game);
	}
	else
	{
		wait_enemy(game);
		read_new_map(game);
		check_end(game);
	}
	start_fight(game);
}

void	start_filler(void)
{
	char	*inp;
	t_fill	*game;

	game = (t_fill*)malloc(sizeof(t_fill));
	get_next_line(STDIN_FILENO, &inp);
	game->xo = 'X';
	if (ft_strstr(inp, "filler") != NULL)
		game->xo = 'O';
	ft_printf("My symbol:%c\n", game->xo);
	get_next_line(STDIN_FILENO, &inp);
	get_next_line(STDIN_FILENO, &inp);
	inp = inp + 8;
	game->map_size[0] = ft_atoi(inp);
	while (*inp != 32)
		inp++;
	game->map_size[1] = ft_atoi(inp);
	ft_printf("Map Size:[%i][%i]", game->map_size[0], game->map_size[1]);
	start_play(game);
}
