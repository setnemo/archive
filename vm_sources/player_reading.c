/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_reading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:26:53 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 15:26:54 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

void		numerate_remaining_players(void)
{
	int		i;
	int		j;

	i = g_g.num_of_players;
	while (i)
	{
		i--;
		if (g_g.players[i].index >= 0)
			continue ;
		j = -1;
		while (++j < MAX_PLAYERS)
			if (!g_g.taken_index[j])
			{
				g_g.players[i].index = j;
				g_g.taken_index[j] = 1;
				break ;
			}
	}
}

void		validate_numeration(void)
{
	int		i;
	int		j;

	i = MAX_PLAYERS;
	while (i > g_g.num_of_players)
	{
		i--;
		if (g_g.taken_index[i])
		{
			j = -1;
			while (++j < g_g.num_of_players)
				if (g_g.players[j].index == i)
					invalid_palyer_index(g_g.players[j].filename);
		}
	}
}
