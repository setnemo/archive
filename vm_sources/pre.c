/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:13:51 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/21 16:13:52 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "encurse.h"
#include <stdlib.h>
#include <ncurses.h>

extern t_global	g_g;
extern t_curs *g_b;

static void	alloc_players(void)
{
	int	j;

	j = -1;
	while (++j < MAX_PLAYERS)
	{
		g_g.players[j].index = -1;
		MALL(g_g.players[j].name =
			(char*)ft_memalloc(sizeof(char) * PROG_NAME_LENGTH));
		MALL(g_g.players[j].comment =
			(char*)ft_memalloc(sizeof(char) * COMMENT_LENGTH));
		MALL(g_g.players[j].field =
			(unsigned char*)ft_memalloc(sizeof(unsigned char) *
				CHAMP_MAX_SIZE));
	}
}

static void	zero_vars(void)
{
	g_g.dump_cycle = -1;
	g_g.num_of_players = 0;
	g_g.period_lives = 0;
	g_g.cycle_to_die = CYCLE_TO_DIE;
	g_g.checks = 0;
	g_g.last_live = 0;
	g_g.any_live = 0;
	g_g.num_of_processes = 0;
	g_g.cycle = 0;
	g_g.total_cycle = 0;
	g_g.secret_var = 0;
	g_g.kill = 0;
	g_g.to_visualise = 0;
	g_g.log_flag1 = 0;
	g_g.log_flag2 = 0;
	g_g.silent_live = 0;
	g_b->sleep = 1;
	g_b->music = 1;
	g_b->treck = 1;
}

void		init_globals(void)
{
	alloc_players();
	MALL(g_g.taken_index = (_Bool*)ft_memalloc(sizeof(_Bool) * MAX_PLAYERS));
	MALL(g_g.field =
		(unsigned char*)ft_memalloc(sizeof(unsigned char) * MEM_SIZE));
	MALL(g_g.proc = (t_process**)malloc(sizeof(t_process*)));
	MALL(g_b = (t_curs*)ft_memalloc(sizeof(t_curs)));
	MALL(g_b->map = (int *)ft_memalloc(sizeof(int) * MEM_SIZE));
	MALL(g_b->live = (int16_t *)ft_memalloc(sizeof(int16_t) * MAX_PLAYERS));
	MALL(g_g.live = (int*)ft_memalloc(sizeof(int) * MAX_PLAYERS));
	*g_g.proc = NULL;
	zero_vars();
}
