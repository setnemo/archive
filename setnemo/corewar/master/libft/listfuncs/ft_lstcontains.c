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

t_list	*ft_lstcontains_cont(t_list *t, void *cont, size_t sofcont)
{
	while (t)
	{
		if (!(ft_memcmp(t->content, cont, sofcont)))
			return (t);
		t = t->next;
	}
	return (NULL);
}
