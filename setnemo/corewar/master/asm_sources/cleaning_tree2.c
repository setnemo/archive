/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_tree2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/04/28 11:49:33 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "error_asm.h"
#include "op.h"

void		cleaning_asm_lst_lst_spltd(t_spl *lst)
{
	t_list	*ptr;
	t_list	*ptr2;
	int		i;

	i = 0;
	if (lst->lbl)
		ft_strdel(&lst->lbl);
	if (lst->op_code != NULL)
		ft_strdel(&(lst->op_code));
	while (i < 3)
	{
		if (lst->islbl[i])
			ft_strdel(&(lst->islbl[i]));
		i++;
	}
	ptr = lst->args;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		if (ptr2->content)
			free(ptr2->content);
		free(ptr2);
	}
}

void		cleaning_asm_lst_spltd(t_list *lst)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		if (ptr2->content)
		{
			cleaning_asm_lst_lst_spltd(ptr2->content);
			free(ptr2->content);
		}
		free(ptr2);
	}
}

void		cleaning_asm_lst_lines(t_list *lst)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(ptr2->content);
		free(ptr2);
	}
}

void		cleaning_asm_lst_lbls(t_list *lst)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(((t_lbl*)ptr2->content)->name);
		free(ptr2->content);
		free(ptr2);
	}
}

void		cleaning_asm_lst_instr(t_list *lst)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(ptr2->content);
		free(ptr2);
	}
}
