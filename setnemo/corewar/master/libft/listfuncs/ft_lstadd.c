/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:20:26 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 17:20:26 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_structures.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!alst)
		return ;
	if (new)
		new->next = *alst;
	*alst = new;
}
