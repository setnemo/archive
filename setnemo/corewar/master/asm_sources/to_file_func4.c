/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_file_func4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/04/28 11:49:33 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "op.h"
#define SUMARR(x, y) (x += (y[0] + y[1] + y[2] + y[3]))

int			setfixsize(t_asmlst *file_lst, int j)
{
	int ret;

	if (file_lst->bytecode[j] == 1)
	{
		ret = 0xFF;
		return (ret);
	}
	if (file_lst->bytecode[j] == 3)
	{
		ret = 0xFFFF;
		return (ret);
	}
	if (file_lst->labelsize == 2)
	{
		ret = 0xFFFF;
		return (ret);
	}
	ret = 0xFFFFFFFF;
	return (ret);
}

void		goup(t_asmlst *file_lst, char *str, int flag, int j)
{
	int			allb;
	t_asmlst	*lst;

	allb = 0;
	while (file_lst && --flag)
		file_lst = file_lst->next;
	lst = file_lst;
	while (file_lst)
	{
		if (file_lst->label && ft_strequ(str, file_lst->label))
			break ;
		SUMARR(allb, file_lst->listsize);
		file_lst = file_lst->next;
	}
	lst->value_arg[j] = allb;
}

void		goback(t_asmlst *file_lst, int flag, int j)
{
	int			allb;
	int			fix;
	t_asmlst	*lst;

	allb = 0;
	lst = file_lst;
	if (lst->number != 1)
	{
		if (lst->number == 0)
			lst->number = 1;
		file_lst = file_lst->next;
	}
	lst = file_lst;
	while (file_lst && flag--)
	{
		SUMARR(allb, file_lst->listsize);
		if (file_lst->next)
			file_lst = file_lst->next;
		else
			break ;
	}
	fix = setfixsize(file_lst, j);
	fix -= --allb;
	file_lst->value_arg[j] = fix;
}

void		get_labelvaluesize(t_asmlst *file_lst, char *str, int i, int j)
{
	int			it[3];
	t_asmlst	*lst;
	t_asmlst	*lst2;

	lst = file_lst;
	it[0] = 0;
	it[1] = 0;
	it[2] = i;
	while (file_lst && it[2]--)
	{
		it[1]++;
		if (file_lst->label && ft_strequ(str, file_lst->label))
		{
			lst2 = file_lst;
			it[0] = it[1];
		}
		file_lst = file_lst->next;
	}
	if (it[0] == 2)
		lst2->prev->number = 0;
	if (!it[0])
		goup(lst, str, i, j);
	else
		(lst2->prev) ? goback(lst2->prev, i - it[0], j) :
	goback(lst2, i - it[0], j);
}
