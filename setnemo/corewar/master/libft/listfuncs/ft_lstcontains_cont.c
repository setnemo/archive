/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcontains_cont.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 12:54:38 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/20 12:54:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

t_list	*ft_lstcontains(t_list *t, void *data, size_t size)
{
	while (t)
	{
		if (t->content_size == size && !(ft_memcmp(t->content, data, size)))
			return (t);
		t = t->next;
	}
	return (NULL);
}
