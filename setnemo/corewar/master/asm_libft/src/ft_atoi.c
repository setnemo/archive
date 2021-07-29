/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:17:34 by oantonen          #+#    #+#             */
/*   Updated: 2018/02/23 18:34:38 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned long	checkmax(unsigned long res, int sign)
{
	if (res > 9223372036854775806 && sign == 1)
		return (-1);
	else if (res > 9223372036854775807 && sign == -1)
		return (0);
	return (res);
}

int						ft_atoi(const char *str)
{
	unsigned long long	res;
	int					sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') && *str)
	{
		res = res * 10 + (*str - '0') % 10;
		str++;
	}
	res = checkmax(res, sign);
	return (res * sign);
}
