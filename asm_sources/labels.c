/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:18:38 by oantonen          #+#    #+#             */
/*   Updated: 2018/05/06 15:03:44 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

void	check_duplic(char *check_lbl, t_list *lbl_list, int line)
{
	char	*lbl;
	t_list	*ptr;

	ptr = lbl_list;
	lbl = ((t_lbl*)ptr->content)->name;
	while (ptr)
	{
		lbl = ((t_lbl*)ptr->content)->name;
		if (ft_strequ(lbl, check_lbl))
		{
			print_errors2(1, "duplicate label", check_lbl, line);
			break ;
		}
		ptr = ptr->next;
	}
}

t_spl	*get_instr(t_list *spltd, int i)
{
	int		line;

	while (spltd)
	{
		line = ((t_spl*)spltd->content)->ln_nb;
		if (i == line)
		{
			return (spltd->content);
		}
		spltd = spltd->next;
	}
	return (NULL);
}

int		check_lbl(char *s, int line)
{
	int		i;
	char	*s2;

	i = 0;
	if (!ft_strchr(s, LABEL_CHAR))
		return (0);
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		if (LABEL_CHAR == s[i] && i != 0)
			return (i);
		if (!ft_strchr(LABEL_CHARS, s[i]))
		{
			s2 = ft_strsub(s, 0, i + 1);
			print_errors2(3, "[LABEL]", s2, line);
			ft_strdel(&s2);
		}
		i++;
	}
	return (0);
}

void	save_lbl(t_fls *file, t_list *instr)
{
	t_lbl	*lb1;
	int		i;
	char	*s;

	lb1 = (t_lbl*)ft_memalloc(sizeof(t_lbl));
	s = (char*)instr->content;
	i = check_lbl(s, instr->content_size);
	lb1->name = ft_strsub(s, 0, i);
	if (file->lbls)
		check_duplic(lb1->name, file->lbls, instr->content_size);
	if (!check_empty(&s[i + 1]))
	{
		lb1->instr = get_instr(file->spltd, instr->content_size);
		ft_list_push_back(&(file->lbls), ft_lstnew(lb1, 0));
	}
	else if (instr->next != NULL && !check_lbl(instr->next->content,
		instr->content_size))
	{
		lb1->instr = get_instr(file->spltd, instr->next->content_size);
		ft_list_push_back(&(file->lbls), ft_lstnew(lb1, 0));
	}
	else
		ft_list_push_back(&(file->lbls), ft_lstnew(lb1, 0));
}

void	split_labels(t_fls *file, t_list *instr)
{
	t_list	*ptr;

	ptr = NULL;
	while (instr)
	{
		if (check_lbl(instr->content, instr->content_size) && !g_is_err)
			save_lbl(file, instr);
		if (g_is_err)
			return ;
		instr = instr->next;
	}
}
