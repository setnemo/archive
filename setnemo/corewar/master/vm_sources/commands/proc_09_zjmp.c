/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_zjmp.c                                        :+:      :+:    :+:   */
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

void			proc_zjump(void *data)
{
	t_process	*proc;

	proc = (t_process*)data;
	if (g_g.log_flag1)
		ft_printf("P%5d | zjmp %d %s\n", proc->secret_num + 1,
			(short)((get_int(proc->pc + 1, 2))),
			proc->carry ? "OK" : "FAILED");
	print_move(proc, 3);
	if (proc->carry)
		proc->pc = set_pos(proc->pc +
			(short)((get_int(proc->pc + 1, 2))) % IDX_MOD);
	else
		proc->pc = set_pos(proc->pc + 3);
}
