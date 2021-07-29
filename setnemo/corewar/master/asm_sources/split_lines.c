/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:20:44 by oantonen          #+#    #+#             */
/*   Updated: 2018/05/06 14:36:27 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

void	save_str(int type, char *str, int *k, t_spl *i_spl)
{
	char	*s;
	char	**args;

	if (type == 1)
	{
		s = ft_strsub(str - *k + 1, 0, *k - 1);
		i_spl->lbl = ft_strtrim(s);
		ft_strdel(&s);
	}
	else if (type == 2)
	{
		i_spl->op_code = ft_strsub(str - *k, 0, *k);
		args = ft_strsplit(str, ',');
		*k = 0;
		while (args[*k])
		{
			s = ft_strtrim(args[*k]);
			ft_list_push_back(&(i_spl->args), ft_lstnew(s, 0));
			ft_strdel(&args[*k]);
			(*k)++;
		}
		i_spl->q_arg = *k;
		free(args);
	}
	*k = 0;
}

int		token(char c, int k, t_spl *i_spl)
{
	if (c == LABEL_CHAR && i_spl->lbl == NULL)
		return (1);
	else if ((c == ' ' || c == '\t') && !i_spl->op_code && k != 0)
		return (2);
	return (0);
}

void	if_not_splitted(t_spl **i_spl, char *str)
{
	t_spl	*i_spl2;
	int		i;

	i_spl2 = *i_spl;
	if (i_spl2->lbl == NULL && i_spl2->op_code == NULL)
		i_spl2->op_code = ft_strdup(str);
	else if (i_spl2->lbl && i_spl2->op_code == NULL)
	{
		i = ft_strchr(str, ':') - str + 1;
		if (!check_empty(&str[i]))
			i_spl2->op_code = ft_strsub(str, i, ft_strlen(&str[i]));
	}
}

void	split_cur_line(t_list **bgng, char *str, int ln_nb)
{
	int		i;
	int		k;
	int		type;
	t_spl	*i_spl;

	i = 0;
	k = 0;
	i_spl = (t_spl*)ft_memalloc(sizeof(t_spl));
	i_spl->op_code = NULL;
	i_spl->ln_nb = ln_nb;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			k++;
		type = token(str[i], k, i_spl);
		if (type)
			save_str(type, &str[i], &k, i_spl);
		if (type == 2)
			break ;
		i++;
	}
	if_not_splitted(&i_spl, str);
	ft_list_push_back(bgng, ft_lstnew(i_spl, 0));
}

void	split_lines(t_fls *file, t_list *instr)
{
	int		i;
	t_list	*spl_i;
	t_list	*ptr;
	char	*s;

	spl_i = NULL;
	i = 0;
	while (instr)
	{
		split_cur_line(&spl_i, instr->content, instr->content_size);
		instr = instr->next;
	}
	ptr = spl_i;
	while (ptr)
	{
		s = ((t_spl*)ptr->content)->op_code;
		if (s != NULL)
			i++;
		ptr = ptr->next;
	}
	if (i == 0)
		print_errors2(0, "No instruction was found", "END", file->line);
	file->spltd = spl_i;
}
