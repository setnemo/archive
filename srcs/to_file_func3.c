/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_file_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/04/28 11:49:33 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "error_asm.h"
#include "op.h"
#define SUMARR(x, y) (x += (y[0] + y[1] + y[2] + y[3]))
#define GL get_labelvaluesize

static void	get_lblbcvadata(t_asmlst *file_lst, t_spl *spl)
{
	int			i;

	i = 0;
	while (i < 3)
	{
		if (spl->islbl[i])
			file_lst->islabel[i] = ft_strdup(spl->islbl[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		file_lst->bytecode[i] = spl->bc[i];
		i++;
	}
	i = 0;
	while (i < 3)
	{
		file_lst->value_arg[i] = spl->value[i];
		i++;
	}
}

void		read_tree(t_asmlst *file_lst, t_spl *spl, t_list *tmp)
{
	while (tmp)
	{
		spl = (t_spl*)tmp->content;
		if (spl->lbl)
			file_lst->label = ft_strdup(spl->lbl);
		if (!spl->op_code && tmp->next)
		{
			spl = (t_spl*)tmp->next->content;
			tmp = tmp->next;
		}
		if (spl->op_code)
			file_lst->op_code = ft_strdup(spl->op_code);
		file_lst->count_arg = spl->q_arg;
		get_lblbcvadata(file_lst, spl);
		if (tmp->next != NULL)
		{
			spl = (t_spl*)tmp->next->content;
			tmp = tmp->next;
			file_lst->next = (t_asmlst*)malloc(sizeof(t_asmlst));
			file_lst = file_lst->next;
			ft_bzero(file_lst, sizeof(t_asmlst));
		}
		else
			break ;
	}
}

void		get_file_lst(t_asmlst *file_lst, t_asm *data, int i, int countlst)
{
	while (file_lst)
	{
		file_lst->octal = get_octal(file_lst->op_code);
		file_lst->labelsize = get_labelsize(file_lst->op_code);
		file_lst->opcodevalue = get_opcodevalue(file_lst->op_code);
		if (file_lst->octal)
			file_lst->octalvalue = get_octalvalue(file_lst->bytecode);
		get_listsize(file_lst);
		SUMARR(data->allbytes, file_lst->listsize);
		file_lst = file_lst->next;
	}
	file_lst = data->next;
	while (file_lst && ++countlst)
	{
		i = 0;
		while (i < 3)
		{
			if (file_lst->islabel[i])
				GL(data->next, file_lst->islabel[i], countlst - 1, i);
			i++;
		}
		file_lst = file_lst->next;
	}
}
