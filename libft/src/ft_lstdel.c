/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:33:04 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/18 21:07:00 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*ptr;

	ptr = NULL;
	if (!alst || !*alst)
		return ;
	if (del)
		while (*alst != NULL)
		{
			ptr = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = ptr;
		}
}
