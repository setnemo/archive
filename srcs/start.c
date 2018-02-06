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

void	start_play(t_fill *game)
{

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
	ft_printf("My symbol:%c\n", game->xo)
	get_next_line(STDIN_FILENO, &inp);
	get_next_line(STDIN_FILENO, &inp);
	inp = inp + 8;
	game->map_size[0] = ft_atoi(inp);
	while (*inp != 32)
		inp++;
	game->map_size[1] = ft_atoi(inp);
	ft_printf("Map Size:[%i][%i]", game->map_size[0], game->map_size[1])
	start_play(game);
}
