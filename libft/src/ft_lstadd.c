/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:24:04 by apakhomo          #+#    #+#             */
/*   Updated: 2017/11/11 15:24:05 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}

void		ft_list_push_back(t_list **begin_list, t_list *new)
{
	t_list	*ptr;

	ptr = NULL;
	if (begin_list)
	{
		if (*begin_list == NULL)
		{
			*begin_list = new;
			(*begin_list)->next = NULL;
		}
		else
		{
			ptr = *begin_list;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
		}
	}
}
