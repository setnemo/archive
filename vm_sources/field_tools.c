/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:29:56 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/19 14:29:57 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern t_global	g_g;

unsigned char	get_field_val(int pos)
{
	return (g_g.field[(MEM_SIZE + pos) % MEM_SIZE]);
}

void			set_field_val(int pos, unsigned char val, int playernum)
{
	g_g.field[(MEM_SIZE + pos) % MEM_SIZE] = val;
	if (g_g.to_visualise == 1)
		load_player((MEM_SIZE + pos) % MEM_SIZE, playernum);
}

int				set_pos(int pos)
{
	return ((MEM_SIZE + pos) % MEM_SIZE);
}

static int		get_two_bits(int pos, int from)
{
	int t;

	t = get_field_val(pos);
	t = t << from;
	t = (unsigned char)t;
	t = t >> 6;
	return (t);
}

t_codes			coding_byte(int pos)
{
	t_codes	ans;

	ans.t[0] = get_two_bits(pos, 0);
	ans.t[1] = get_two_bits(pos, 2);
	ans.t[2] = get_two_bits(pos, 4);
	return (ans);
}
