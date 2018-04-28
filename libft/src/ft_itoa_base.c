/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:30:44 by oantonen          #+#    #+#             */
/*   Updated: 2017/12/28 21:09:02 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		char_count(long long int value, int base)
{
	int i;

	i = 0;
	if (value == 0)
		return (1);
	if (value < 0 && base == 10)
		i = 1;
	while (value)
	{
		value = value / base;
		i++;
	}
	return (i);
}

char			*ft_itoa_base(long long int value, int base)
{
	char		*base_num;
	char		*res;
	int			i;

	base_num = "0123456789ABCDEF";
	i = char_count(value, base);
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (value < 0)
	{
		(base) == 10 ? res[0] = '-' : res[0];
		value = -value;
	}
	while (value != 0)
	{
		if (value % base > 9)
			res[i - 1] = base_num[value % base];
		else
			res[i - 1] = value % base + '0';
		value = value / base;
		i--;
	}
	return (res);
}
