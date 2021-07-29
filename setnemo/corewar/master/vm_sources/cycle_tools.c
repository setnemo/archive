/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_tools.c                                      :+:      :+:    :+:   */
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

extern t_global	g_g;
extern t_func	g_funcs[];
extern t_curs	*g_b;

static int	ygdb_1(t_process **temp, t_process **prev)
{
	if ((*temp)->live)
	{
		(*temp)->live = 0;
		(*prev) = (*temp);
		(*temp) = (*temp)->next;
		return (1);
	}
	return (0);
}

void		you_gonna_die_bitch(void)
{
	t_process	*temp;
	t_process	*prev;
	int			i;

	temp = *g_g.proc;
	while (temp)
	{
		if (ygdb_1(&temp, &prev))
			continue;
		if (temp == *g_g.proc)
		{
			temp = (*g_g.proc)->next;
			free_proc(*g_g.proc);
			*g_g.proc = temp;
			continue;
		}
		temp = temp->next;
		free_proc(prev->next);
		prev->next = temp;
	}
	i = -1;
	while (++i < g_g.num_of_players)
		g_g.live[i] = 0;
}

void		parse_commands(void)
{
	t_process	*proc;

	proc = *g_g.proc;
	while (proc)
	{
		if (!proc->func)
			parse_command(proc);
		proc = proc->next;
	}
}

void		run_cycle_step(void)
{
	t_process	*proc;

	proc = *g_g.proc;
	while (proc)
	{
		proc->sleep--;
		if (proc->sleep == 0)
		{
			if (g_g.to_visualise)
				erace_old(proc->pc);
			proc->func((void*)proc);
			proc->func = NULL;
			if (g_g.to_visualise)
				draw_new(proc->pc);
		}
		proc = proc->next;
	}
	parse_commands();
}

void		ctd_check(void)
{
	g_g.checks++;
	if (g_g.period_lives >= NBR_LIVE || g_g.checks == MAX_CHECKS)
	{
		g_g.cycle_to_die -= CYCLE_DELTA;
		if (g_g.cycle_to_die < 1)
			g_g.cycle_to_die = 1;
		g_g.checks = 0;
		g_g.period_lives = 0;
		return ;
	}
}
