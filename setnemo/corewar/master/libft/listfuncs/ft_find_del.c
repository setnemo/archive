/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:04:29 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/23 20:04:29 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int		ft_find_del(t_list **list, void *data, size_t size)
{
	t_list	*t;
	t_list	*f;

	if (!list || !(*list))
		return (0);
	t = *list;
	while (t->next)
		if (t->next->content_size == size &&
			!(ft_memcmp(t->next->content, data, size)))
		{
			if (t == *list)
			{
				f = (*list)->next;
				ft_lstdelone(&t, NULL);
				*list = f;
			}
			else
			{
				f = t->next->next;
				ft_lstdelone(&(t->next), NULL);
				t->next = f;
			}
			return (1);
		}
	return (0);
}
