/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:18:38 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/31 17:57:57 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

t_spl	*get_instr(t_list *spltd, int i)
{
	t_spl	*cur;
	int 	line;

	while (spltd)
	{
		line = ((t_spl*)spltd->content)->ln_nb;
		// ft_printf("line=%d\n", line);
		// ft_printf("i=%d\n", i);
		if (i == line)
		{
			// ft_printf("instr=%s\n", ((t_spl*)spltd->content)->instr);
			return (spltd->content);
		}
		spltd = spltd->next;
	}
	return (NULL);
}

int 		check_lbl(char	*s)
{
	int 	i;

	i = 0;
	// ft_printf("s=%s\n", s);
	while (s[i] && s[i] != ' ' && s[i] != '\t')
	{
		// ft_printf("s=%s\n", s);
		if (LABEL_CHAR == s[i] && i != 0)
			return (i);
		if (!ft_strchr(LABEL_CHARS, s[i]))
			print_errors(31);
		i++;
	}
	return (0);
}

int 		save_lbl(t_fls *file, char *str, t_list *instr)
{
	t_lbl	*lb1;
	int		i;
	char	*s;

	lb1 = (t_lbl*)ft_memalloc(sizeof(t_lbl));
	s = (char*)instr->content;
	i = check_lbl(s);
	lb1->name = ft_strsub(s, 0, i);
	if (!check_empty(&s[i + 1]))
	{
		lb1->instr = get_instr(file->spltd, instr->content_size);
		ft_list_push_back(&(file->lbls), ft_lstnew(lb1, 0));
	}
	else if (instr->next != NULL)
	{
		if (!check_lbl(instr->next->content))
		{
			lb1->instr = get_instr(file->spltd, instr->next->content_size);
			ft_list_push_back(&(file->lbls), ft_lstnew(lb1, 0));
		}
	}
	else
		ft_list_push_back(&(file->lbls), ft_lstnew(lb1, 0));
	return (1);
}

void	split_labels(t_fls *file, t_list *instr)
{
	while (instr)
	{
		if (check_lbl(instr->content))
			save_lbl(file, instr->content, instr);
		instr = instr->next;
	}
	t_list *ptr = file->lbls;
	// while (ptr)
	// {
	// 	ft_printf("lbl=%s: ", ((t_lbl*)ptr->content)->name);
	// 	if (((t_lbl*)ptr->content)->instr)
	// 		ft_printf("%s\n", ((t_lbl*)ptr->content)->instr->instr);
	// 	ptr = ptr->next;
	// }
}