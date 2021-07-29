/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:20:46 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 17:20:46 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_structures.h"

static void	list_add_to_end(t_list **begin_list, t_list *elem)
{
	t_list	*ans;

	ans = *begin_list;
	if (ans)
	{
		while (ans->next)
			ans = ans->next;
		ans->next = elem;
	}
	else
		*begin_list = elem;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*iter;
	t_list	*ans;

	ans = NULL;
	if (!f)
		return (NULL);
	while (lst)
	{
		iter = lst->next;
		list_add_to_end(&ans, (*f)(lst));
		lst = iter;
	}
	return (ans);
}
