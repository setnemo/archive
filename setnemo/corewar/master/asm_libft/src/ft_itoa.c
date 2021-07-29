/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:54:42 by oantonen          #+#    #+#             */
/*   Updated: 2017/12/27 12:21:05 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		arr_length(long long int n)
{
	int				i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char			*fresh;
	int				chars;
	long long int	long_n;

	long_n = n;
	chars = arr_length(n);
	if (!(fresh = ft_strnew(chars)))
		return (NULL);
	if (long_n < 0)
	{
		fresh[0] = '-';
		long_n = -long_n;
	}
	else if (long_n == 0)
	{
		fresh[0] = '0';
		return (fresh);
	}
	while (long_n != 0)
	{
		fresh[chars - 1] = long_n % 10 + '0';
		long_n = long_n / 10;
		chars--;
	}
	return (fresh);
}
