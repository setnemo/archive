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

void	check_map(t_fill *game)
{
	char	*line;
	char	*temp;

	if (!(get_next_line(STDIN_FILENO, &line)))
	{
		if (game->map)
			free_map(game);
		if (game->bit)
			free_bit(game);
		exit(0);
	}
	temp = line;
	line = line + 8;
	game->map_size[0] = ft_atoi(line);
	while (*line != 32)
		line++;
	game->map_size[1] = ft_atoi(line);
	ft_strdel(&temp);
	get_next_line(STDIN_FILENO, &line);
	ft_strdel(&line);
}

void	read_bit(t_fill *game)
{
	int		a;
	char	*line;
	char	*temp;

	if (game->bit)
		free_bit(game);
	get_next_line(STDIN_FILENO, &line);
	temp = line;
	line += 6;
	game->bit_size[0] = ft_atoi(line);
	while (*line != 32)
		line++;
	game->bit_size[1] = ft_atoi(line);
	game->bit = (char**)malloc((sizeof(char*) * game->bit_size[0]) + 1);
	game->bit[game->bit_size[0]] = NULL;
	a = 0;
	ft_strdel(&temp);
	while (a < game->bit_size[0])
	{
		get_next_line(STDIN_FILENO, &line);
		game->bit[a] = ft_strdup(line);
		ft_strdel(&line);
		a++;
	}
}

void	read_map(t_fill *game)
{
	int		a;
	char	*line;

	check_map(game);
	if (game->map == NULL)
	{
		game->map = (char**)malloc((sizeof(char*) * game->map_size[0]) + 1);
		a = 0;
		while (a < game->map_size[0])
		{
			game->map[a] = NULL;
			a++;
		}
	}
	a = 0;
	while (a < game->map_size[0])
	{
		if (game->map[a])
			ft_strdel(&game->map[a]);
		get_next_line(STDIN_FILENO, &line);
		game->map[a] = ft_strdup(line + 4);
		ft_strdel(&line);
		a++;
	}
}

void	start_play(t_fill *game)
{
	if (game->xo == 'O')
	{
		read_map(game);
		read_bit(game);
		spot_loc(game);
	}
	while (1)
	{
		read_map(game);
		read_bit(game);
		spot_loc(game);
	}
}

int		main(void)
{
	char	*line;
	t_fill	*game;

	game = (t_fill*)malloc(sizeof(t_fill));
	ft_bzero(game, sizeof(t_fill));
	game->map = NULL;
	game->bit = NULL;
	game->spot = NULL;
	game->a_loc = 0;
	get_next_line(STDIN_FILENO, &line);
	game->xo = 'X';
	game->enemy = 'O';
	if (ft_strstr(line, "p1") != NULL)
	{
		game->xo = 'O';
		game->enemy = 'X';
	}
	ft_strdel(&line);
	start_play(game);
	return (0);
}
