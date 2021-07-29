/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:20:38 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 17:20:38 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_structures.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*iter;

	if (!f)
		return ;
	while (lst)
	{
		iter = lst->next;
		(*f)(lst);
		lst = iter;
	}
}
