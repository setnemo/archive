/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:35:38 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/15 17:35:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "encurse.h"
#include <stdlib.h>
#include <ncurses.h>
#include "vm.h"

extern t_global	g_g;
extern t_func	g_funcs[];
extern t_curs	*g_b;

static void	read_and_parse(int ac, char **av)
{
	init_globals();
	parse_input(ac, av);
	numerate_remaining_players();
	validate_numeration();
	set_players();
	if (g_g.dump_cycle == 0)
		print_field();
	if (g_g.to_visualise)
		curse();
	else
		print_participants();
	gen_processes();
}

void		finish_prog(void)
{
	if (g_g.to_visualise)
	{
		pashalka();
		exit_curse_main();
	}
	if (!*g_g.proc)
		print_winner();
}

int			main(int ac, char **av)
{
	read_and_parse(ac, av);
	while (1)
	{
		g_g.kill = g_g.kill == 1 ? 0 : g_g.kill;
		if (!*g_g.proc)
			break ;
		if (g_g.to_visualise)
			++g_b->cycle;
		run_cycle_step();
		g_g.cycle++;
		g_g.total_cycle++;
		if (g_g.cycle == g_g.cycle_to_die)
		{
			g_g.cycle = 0;
			you_gonna_die_bitch();
			ctd_check();
			g_g.period_lives = 0;
		}
		if (g_g.total_cycle == g_g.dump_cycle)
			print_field();
		if (g_g.to_visualise)
			readkey();
	}
	finish_prog();
	return (0);
}
