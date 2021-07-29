/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:25:54 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:25:54 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_isprime(long nb)
{
	long	nbsqrt;
	long	i;

	if (nb < 2)
		return (0);
	if (nb == 2)
		return (1);
	i = 1;
	nbsqrt = ft_sqrt(nb);
	while (++i <= nbsqrt + 1)
		if (nb % i == 0)
			return (0);
	return (1);
}
