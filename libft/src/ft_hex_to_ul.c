/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 09:55:17 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/27 09:55:17 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	hex_to_ul(unsigned char *str)
{
	int				a;
	int				b;
	unsigned char	c;
	unsigned long	ret;

	str = ft_strtolower(str);
	a = 0;
	b = 0;
	ret = 0;
	while (a < 16)
	{
		c = str[b];
		if (str[b])
			b++;
		ret <<= 4;
		if ((c >= '0') && (c <= '9'))
			ret += (c - '0');
		if ((c >= 'a') && (c <= 'f'))
			ret += ((c - 'a') + 10);
		a++;
	}
	return (ret);
}
