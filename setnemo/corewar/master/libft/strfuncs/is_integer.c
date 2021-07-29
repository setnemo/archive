/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:46:35 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/26 14:46:36 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

_Bool	is_integer(char *str)
{
	int i;
	int sign;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	sign = i;
	while (str[i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		else
			i++;
	if (str[i] || i > 10 + sign)
		return (0);
	if (i < 10 + sign)
		return (1);
	if (sign == 0)
	{
		if (ft_strcmp(str, "2147483647") > 0)
			return (0);
		return (1);
	}
	if (ft_strcmp(str, "-2147483648") > 0)
		return (0);
	return (1);
}
