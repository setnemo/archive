/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 20:56:18 by oantonen          #+#    #+#             */
/*   Updated: 2018/05/06 14:35:56 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

int		check_value(char *arg, int type, int *value)
{
	int		i;

	i = (*arg == '-') ? 1 : 0;
	while (arg[i] && (ft_isdigit(arg[i])))
		i++;
	*value = ft_atoi(arg);
	if (arg[i] == '\0' && type == 1)
		return (2);
	else if (arg[i] == '\0' && type == 2)
		return (4);
	else if (arg[i] == '\0' && type == 3)
		return (1);
	return (0);
}

int		check_indirect(char *arg, t_list *lbls, char **islbl, int *value)
{
	t_list	*ptr;

	ptr = lbls;
	if (arg[0] == LABEL_CHAR)
	{
		while (ptr)
		{
			if (ft_strequ(&arg[1], ((t_lbl*)ptr->content)->name))
				break ;
			ptr = ptr->next;
		}
		if (ptr != NULL)
		{
			*islbl = ft_strdup(&arg[1]);
			return (4);
		}
	}
	else
		return (check_value(&arg[0], 2, value));
	return (0);
}

int		check_direct(char *arg, t_list *lbls, char **islbl, int *value)
{
	t_list	*ptr;

	ptr = lbls;
	if (arg[1] == LABEL_CHAR)
	{
		while (ptr)
		{
			if (ft_strequ(&arg[2], ((t_lbl*)ptr->content)->name))
				break ;
			ptr = ptr->next;
		}
		if (ptr != NULL)
		{
			*islbl = ft_strdup(&arg[2]);
			return (2);
		}
	}
	else
		return (check_value(&arg[1], 1, value));
	return (0);
}

int		identify_argtype(char *arg, t_list *lbls, char **islbl, int *value)
{
	if (arg[0] == 'r')
	{
		*value = ft_atoi(&arg[1]);
		if (check_value(&arg[1], 3, value) == 1)
			if (*value >= 1 && *value <= REG_NUMBER)
				return (1);
	}
	else if (arg[0] == DIRECT_CHAR)
		return (check_direct(arg, lbls, islbl, value));
	else if (ft_isdigit(arg[0]) || (arg[0] == LABEL_CHAR || arg[0] == '-'))
		return (check_indirect(arg, lbls, islbl, value));
	return (0);
}
