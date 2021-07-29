/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:51:45 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 17:51:46 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <stdlib.h>

extern t_global	g_g;

void		set_players(void)
{
	int	i;
	int j;

	i = -1;
	while (++i < g_g.num_of_players)
		g_g.players[i].startpos = i * MEM_SIZE /
			g_g.num_of_players;
	i = -1;
	while (++i < g_g.num_of_players)
	{
		j = -1;
		while (++j < g_g.players[i].field_size)
			g_g.field[j + g_g.players[i].startpos] = g_g.players[i].field[j];
	}
}

void		print_participants(void)
{
	int	i;

	ft_printf(" || PARTICIPANTS: ||\n");
	i = -1;
	while (++i < g_g.num_of_players)
	{
		ft_printf("=============// Player[%d]\n", i + 1);
		ft_printf("\tName:    \"%.*s\"\n", PROG_NAME_LENGTH,
			g_g.players[i].name);
		ft_printf("\tWeight:   %d\n", g_g.players[i].field_size);
		ft_printf("\tComment: \"%.*s\"\n", COMMENT_LENGTH,
			g_g.players[i].comment);
	}
}

void		print_field(void)
{
	int	i;

	finish_prog();
	ft_printf("\n ||    FIELD:     || \n");
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%0.4x |", i);
		ft_printf(" %02x", g_g.field[i]);
		if (i % 64 == 63)
			ft_printf("\n");
	}
	exit(0);
}

void		print_winner(void)
{
	if (!g_g.any_live)
		g_g.last_live = g_g.num_of_players - 1;
	ft_printf("Contestant %d, ", g_g.last_live + 1);
	ft_printf("\"%s\", has won !\n", g_g.players[g_g.last_live].name);
}
