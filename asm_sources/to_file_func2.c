/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_file_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/04/28 11:49:33 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "op.h"
#define LS2 2
#define LS4 4

void		get_listsize(t_asmlst *file_lst)
{
	int i;

	i = 1;
	if (file_lst->octal)
		file_lst->listsize[0] = 2;
	else
		file_lst->listsize[0] = 1;
	while (i < 4)
	{
		if (file_lst->bytecode[i - 1])
		{
			if (file_lst->bytecode[i - 1] == 1)
				file_lst->listsize[i] = 1;
			if (file_lst->bytecode[i - 1] == 2)
				file_lst->listsize[i] = file_lst->labelsize;
			if (file_lst->bytecode[i - 1] == 3)
				file_lst->listsize[i] = 2;
		}
		i++;
	}
}

int			get_octalvalue(char val[])
{
	int		i;
	short	value;
	int		bit;

	i = 0;
	value = 0;
	bit = 7;
	while (i < 3)
	{
		if (val[i] == 3)
		{
			value |= 1 << bit;
			value |= 1 << (bit - 1);
		}
		if (val[i] == 2)
			value |= 1 << bit;
		if (val[i] == 1)
			value |= 1 << (bit - 1);
		bit -= 2;
		i++;
	}
	return (value);
}

int			get_opcodevalue(char *opcode)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_optab[i].name, opcode))
			break ;
		i++;
	}
	return (g_optab[i].op_code);
}

int			get_labelsize(char *opcode)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_optab[i].name, opcode))
			break ;
		i++;
	}
	if (g_optab[i].op_code > 8 &&
		g_optab[i].op_code != 13 && g_optab[i].op_code != 16)
	{
		return (LS2);
	}
	return (LS4);
}

int			get_octal(char *opcode)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_optab[i].name, opcode))
			break ;
		i++;
	}
	return (g_optab[i].codage);
}
