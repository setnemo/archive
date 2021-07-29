/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:08:15 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/21 16:08:15 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "encurse.h"
#include <stdlib.h>
#include <ncurses.h>

extern t_global	g_g;
extern t_func	g_funcs[];

void	new_process(int pc, int playernum)
{
	t_process	*new_proc;

	g_g.num_of_processes++;
	MALL(new_proc = (t_process*)ft_memalloc(sizeof(t_process)));
	MALL(new_proc->registry =
		(unsigned int*)ft_memalloc(sizeof(unsigned int) * REG_NUMBER + 1));
	new_proc->index = playernum - 1;
	new_proc->registry[1] = -playernum;
	new_proc->pc = pc;
	new_proc->carry = 0;
	new_proc->live = 0;
	new_proc->secret_num = g_g.secret_var++;
	new_proc->next = *g_g.proc;
	*g_g.proc = new_proc;
	parse_command(new_proc);
}

void	copy_process(int pc, t_process *proc)
{
	int			i;
	t_process	*new_proc;

	g_g.num_of_processes++;
	MALL(new_proc = (t_process*)ft_memalloc(sizeof(t_process)));
	MALL(new_proc->registry =
		(unsigned int*)ft_memalloc(sizeof(unsigned int) * REG_NUMBER + 1));
	new_proc->index = proc->index;
	i = 0;
	while (++i <= REG_NUMBER)
		new_proc->registry[i] = proc->registry[i];
	new_proc->pc = pc % MEM_SIZE;
	new_proc->carry = proc->carry;
	new_proc->live = proc->live;
	new_proc->secret_num = g_g.secret_var++;
	new_proc->next = *g_g.proc;
	*g_g.proc = new_proc;
	parse_command(new_proc);
	if (g_g.to_visualise == 1)
		draw_new(new_proc->pc);
}

void	gen_processes(void)
{
	int	i;
	int j;

	i = -1;
	while (++i < g_g.num_of_players)
	{
		j = -1;
		while (++j < g_g.num_of_players)
			if (g_g.players[j].index == i)
			{
				new_process(g_g.players[j].startpos, j + 1);
				break ;
			}
	}
}

void	free_proc(t_process *proc)
{
	g_g.num_of_processes--;
	if (g_g.to_visualise)
		erace_old(proc->pc);
	g_g.kill = 1;
	free(proc->registry);
	free(proc);
}

void	parse_command(t_process *p)
{
	int i;

	i = -1;
	while (++i < NUM_OF_FUNCS)
		if (g_g.field[p->pc] == g_funcs[i].hex)
		{
			p->func = g_funcs[i].func;
			p->sleep = g_funcs[i].sleep;
			p->label_size = g_funcs[i].label_size;
			break ;
		}
	if (i == NUM_OF_FUNCS)
	{
		p->func = &proc_invalid;
		p->sleep = 1;
		p->label_size = 0;
	}
}
