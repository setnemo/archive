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
	arg[0] = proc->registry[arg[0]];
	if (cod_b.t[1] == TREG)
		arg[1] = proc->registry[arg[1]];
	else if (cod_b.t[1] == TIND)
		arg[1] = get_int(proc->pc + (short)(arg[1]) % IDX_MOD, 4);
	if (cod_b.t[2] == TREG)
		arg[2] = proc->registry[arg[2]];
}

static void	print_log(t_process *proc, int *arg)
{
	if (g_g.log_flag1)
	{
		ft_printf("%d %d\n", arg[1], arg[2]);
		ft_printf("       | -> store to %d + %d = %d ",
			arg[1], arg[2], arg[1] + arg[2]);
		ft_printf("(with pc and mod %d)\n",
			proc->pc + (arg[1] + arg[2]) % IDX_MOD);
	}
}

void		proc_sti(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			toskip;
	int			arg[3];

	cod_b = get_cod_b(&toskip, &proc, data);
	if (cod_b.t[0] != TREG || !cod_b.t[1] ||
		(cod_b.t[2] != TDIR && cod_b.t[2] != TREG) ||
		!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip) ||
		!parse_arg(cod_b.t[2], proc, &arg[2], &toskip))
	{
		print_move(proc, count_total_skip(cod_b, 1, 3, proc->label_size));
		proc->pc = set_pos(proc->pc +
			count_total_skip(cod_b, 1, 3, proc->label_size));
		return ;
	}
	if (g_g.log_flag1)
		ft_printf("P%5d | sti r%d ", proc->secret_num + 1, arg[0]);
	parse_args(cod_b, arg, proc);
	set_int(proc->pc + (arg[1] + arg[2]) % IDX_MOD, 4, arg[0], proc->index);
	print_log(proc, arg);
	print_move(proc, toskip);
	proc->pc = set_pos(proc->pc + toskip);
}
