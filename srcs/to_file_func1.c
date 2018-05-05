/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_file_func1.c                                    :+:      :+:    :+:   */
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
#define GL get_labelvaluesize

void		get_file_lst(t_asm *data, int i, int countlst)
{
	t_asmlst	*file_lst = NULL;

	file_lst = data->next;

	while (file_lst)
	{
		if (file_lst->empty == 0)
		{
			file_lst->octal = get_octal(file_lst->op_code);
			file_lst->labelsize = get_labelsize(file_lst->op_code);
			file_lst->opcodevalue = get_opcodevalue(file_lst->op_code);
			if (file_lst->octal)
				file_lst->octalvalue = get_octalvalue(file_lst->bytecode);
			get_listsize(file_lst);
			SUMARR(data->allbytes, file_lst->listsize);		
		}
		file_lst = file_lst->next;
	}
	file_lst = data->next;
	while (file_lst && ++countlst)
	{
		i = 0;
		while (i < 3)
		{
			if (file_lst->islabel[i])
				GL(data->next, file_lst->islabel[i], countlst, i);
			i++;
		}
		file_lst = file_lst->next;
	}
}

int			to_file(t_list **fl_lst, t_asm *data)
{
	t_fls		*fls;
	t_asmlst	*file_lst = NULL;
	t_asmlst	*back = NULL;

	fls = (*fl_lst)->content;
	data->filename = ft_strdup(fls->name);
	data->filecomment = ft_strdup(fls->cmnt);
	file_lst = (t_asmlst*)malloc(sizeof(t_asmlst));
	data->next = file_lst;
	ft_bzero(file_lst, sizeof(t_asmlst));
	file_lst = data->next;
	read_tree(file_lst,NULL, fls->spltd);
	int num = 0;
	while (file_lst)
	{
		num++;
		file_lst->number = num;
		if (file_lst->next)
		{
			back = file_lst;
			file_lst = file_lst->next;
			file_lst->prev = back;
		}
		else
			break ;
	}
	get_file_lst(data, 0, 0);
	return (push_data_to_file(data));
}
