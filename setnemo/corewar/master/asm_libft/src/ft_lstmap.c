/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:26:13 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/21 11:59:15 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_delete(t_list **lst)
{
	t_list *ptr;

	ptr = NULL;
	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = ptr;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;
	t_list *head;

	head = NULL;
	if (lst)
	{
		if (!(new_list = f(lst)))
			return (NULL);
		lst = lst->next;
		head = new_list;
		while (lst != NULL)
		{
			if (!(new_list->next = f(lst)))
			{
				ft_delete(&new_list);
				return (NULL);
			}
			new_list = new_list->next;
			lst = lst->next;
		}
	}
	return (head);
}
