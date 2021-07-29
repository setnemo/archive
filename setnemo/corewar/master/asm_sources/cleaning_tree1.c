/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_tree1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/05/06 15:09:26 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "error_asm.h"
#include "op.h"

int				print_errors2(char err_type, char *token,
	char *err_str, int line)
{
	char	*err;

	err = NULL;
	if (err_type == 1)
	{
		err = "Syntax error at token ";
		ft_printf("%s%s \"%s\"\n", err, token, err_str);
	}
	else if (err_type == 2)
		err = "Invalid argument for ";
	else if (err_type == 0)
		err = "";
	else if (err_type == 3)
		err = "Lexical error ";
	else if (err_type == 4)
		err = "Lexical error at NAME ";
	else if (err_type == 5)
		err = "Lexical error at COMMENT ";
	else if (err_type == 6)
		err = "Invalid instruction at token ";
	if (err_type != 1)
		ft_printf("%s%s \"%s\" at line %d\n", err, token, err_str, line);
	g_is_err = 1;
	return (0);
}

void			asm_del_lst(t_list **begin)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = *begin;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(ptr2->content);
		free(ptr2);
	}
}

static void		clean_data_to_file(t_asm *data)
{
	t_asmlst	*file_lst;
	t_asmlst	*temp;
	int			i;

	file_lst = data->next;
	if (data->filename)
		ft_strdel(&data->filename);
	if (data->filecomment)
		ft_strdel(&data->filecomment);
	while (file_lst)
	{
		temp = file_lst;
		if (temp->label)
			ft_strdel(&temp->label);
		if (temp->op_code)
			ft_strdel(&temp->op_code);
		i = -1;
		while (++i < 3)
		{
			if (temp->islabel[i] != NULL)
				ft_strdel(&temp->islabel[i]);
		}
		file_lst = file_lst->next;
		free(temp);
	}
}

static void		cleaning_asm_lst_sruct(t_fls *fls)
{
	if (fls->name)
		ft_strdel(&fls->name);
	if (fls->cmnt)
		ft_strdel(&fls->cmnt);
	if (fls->lbls)
		cleaning_asm_lst_lbls(fls->lbls);
	if (fls->lines)
		cleaning_asm_lst_lines(fls->lines);
	if (fls->instr)
		cleaning_asm_lst_instr(fls->instr);
	if (fls->spltd)
		cleaning_asm_lst_spltd(fls->spltd);
	free(fls);
}

void			cleaning_asm_lst(t_list **fl_lst, t_list **fl_err, t_asm *data)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *fl_lst;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		if (tmp2->content)
			cleaning_asm_lst_sruct(tmp2->content);
		free(tmp2);
	}
	tmp = *fl_err;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		if (tmp2->content)
			cleaning_asm_lst_sruct(tmp2->content);
		if (tmp2)
			free(tmp2);
	}
	if (data->filename)
		clean_data_to_file(data);
}
