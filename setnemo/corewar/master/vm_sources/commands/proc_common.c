/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:19:13 by nkolosov          #+#    #+#             */
/*   Updated: 2018/04/26 15:19:14 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

void	print_move(t_process *proc, int toskip)
{
	int i;
	int oldpc;

	i = -1;
	if (!g_g.log_flag2 || g_g.to_visualise)
		return ;
	oldpc = proc->pc;
	ft_printf("|CMD| = %d (0x%0.4x -> 0x%0.4x) ",
		toskip, proc->pc, proc->pc + toskip);
	while (++i < toskip)
		ft_printf("%02x ", get_field_val(proc->pc + i));
	ft_printf("\n");
}

t_codes	get_cod_b(int *toskip, t_process **proc, void *data)
{
	t_codes	ret;

	*toskip = COMMAND;
	*proc = (t_process*)data;
	ret = coding_byte((*proc)->pc + *toskip);
	*toskip = *toskip + CODING_BYTE;
	return (ret);
}
