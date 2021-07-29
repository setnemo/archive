/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_fork.c                                        :+:      :+:    :+:   */
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

void			proc_fork_long(void *data)
{
	t_process	*proc;

	proc = (t_process*)data;
	copy_process(proc->pc + (short)(get_int(proc->pc + 1, 2)), proc);
	if (g_g.log_flag1)
		ft_printf("P%5d | lfork %d (%d)\n",
			proc->secret_num + 1, (short)get_int(proc->pc + 1, 2),
			proc->pc + (short)(get_int(proc->pc + 1, 2)));
	print_move(proc, 3);
	proc->pc = set_pos(proc->pc + 3);
}
