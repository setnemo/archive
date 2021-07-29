/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:20:15 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 17:20:15 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if (!alst || !(*alst))
		return ;
	if ((*alst)->next)
		ft_lstdel(&((*alst)->next), del);
	ft_lstdelone(&(*alst), del);
}
