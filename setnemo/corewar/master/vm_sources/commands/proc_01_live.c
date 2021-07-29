/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_live.c                                        :+:      :+:    :+:   */
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

void	proc_live(void *data)
{
	t_process		*proc;
	unsigned int	l;

	proc = (t_process*)data;
	proc->live++;
	g_g.period_lives++;
	l = get_int(proc->pc + 1, 4);
	if (g_g.log_flag1)
		ft_printf("P%5u | live %d\n", proc->secret_num + 1, l);
	l = -(l + 1);
	print_move(proc, 5);
	proc->pc = set_pos(proc->pc + 5);
	if (l >= (unsigned int)g_g.num_of_players)
		return ;
	g_g.any_live = 1;
	if (g_g.to_visualise)
		call_me_baby_i_am_alive(g_g.players[l].index);
	else if (!g_g.silent_live)
		ft_printf("A process shows that player %d (%s) is alive\n",
		l + 1, g_g.players[l].name);
	g_g.last_live = l;
	g_g.live[l]++;
}
