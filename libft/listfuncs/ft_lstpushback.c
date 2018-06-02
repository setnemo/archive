/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:45:52 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/17 14:45:52 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_structures.h"

void	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list	*l;

	if (!alst)
		return ;
	l = *alst;
	if (!l)
		*alst = new;
	else
	{
		while (l->next)
			l = l->next;
		l->next = new;
	}
}
