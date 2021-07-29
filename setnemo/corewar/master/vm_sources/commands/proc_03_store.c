/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:29:56 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/19 14:29:57 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

static void	parse_args(t_codes cod_b, int *arg, t_process *proc)
{
	if (cod_b.t[1] == TREG)
		proc->registry[arg[1]] = proc->registry[arg[0]];
	else
		set_int(proc->pc + ((short)(arg[1]) % IDX_MOD), 4,
			proc->registry[arg[0]], proc->index);
}

void		proc_store(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			toskip;
	int			arg[2];

	cod_b = get_cod_b(&toskip, &proc, data);
	if (cod_b.t[0] != TREG || (cod_b.t[1] != TREG && cod_b.t[1] != TIND) ||
		!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip))
	{
		print_move(proc, count_total_skip(cod_b, 1, 2, proc->label_size));
		proc->pc = set_pos(proc->pc +
			count_total_skip(cod_b, 1, 2, proc->label_size));
		return ;
	}
	if (g_g.log_flag1)
		ft_printf("P%5u | st r%d %d\n", proc->secret_num + 1, arg[0], arg[1]);
	parse_args(cod_b, arg, proc);
	print_move(proc, toskip);
	proc->pc = set_pos(proc->pc + toskip);
}
