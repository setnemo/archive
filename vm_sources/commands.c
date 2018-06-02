/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
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

int		count_total_skip(t_codes c_b, _Bool has_coding, int numofargs, int td)
{
	int		total;
	int		i;

	total = COMMAND;
	total += has_coding ? CODING_BYTE : 0;
	i = -1;
	while (++i < numofargs)
	{
		if (c_b.t[i] == TREG)
			total += T_REG;
		else if (c_b.t[i] == TDIR)
			total += td;
		else if (c_b.t[i] == TIND)
			total += T_IND;
	}
	return (total);
}

int		get_int(int pos, int len)
{
	int		ans;
	int		i;

	ans = 0;
	i = -1;
	while (++i < len)
		ans = (ans << 8) + get_field_val(pos + i);
	return (ans);
}

void	set_int(int pos, int len, UINT val, int playernum)
{
	int i;

	i = len;
	while (i > 0)
	{
		i--;
		set_field_val(pos + i, val, playernum);
		val = (val >> 8);
	}
}

_Bool	parse_arg(int code, t_process *proc, int *arg, int *toskip)
{
	if (code == TREG)
	{
		*arg = get_int(proc->pc + *toskip, T_REG);
		if (*arg < 1 || *arg > REG_NUMBER)
			return (0);
		*toskip = *toskip + T_REG;
	}
	else if (code == TDIR)
	{
		*arg = get_int(proc->pc + *toskip, proc->label_size);
		*toskip = *toskip + proc->label_size;
		if (proc->label_size == 2)
			*arg = (short int)*arg;
	}
	else
	{
		*arg = (short int)(get_int(proc->pc + *toskip, T_IND));
		*toskip = *toskip + T_IND;
	}
	return (1);
}
