/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 21:19:45 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/27 19:20:36 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_push_back(t_list **begin_list, t_list *new)
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
