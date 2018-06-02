/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:05:05 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 13:05:05 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_atoi(const char *str)
{
	long	ans;
	int		multiplier;
	int		i;

	i = 0;
	ans = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||
			str[i] == ' ' || str[i] == '\f' || str[i] == '\r')
		i++;
	multiplier = str[i] == '-' ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - '0';
		i++;
		if (ans < 0)
			return (multiplier < 0 ? 0 : -1);
	}
	return ((int)(ans * multiplier));
}

int		ptr_atoi(char **str)
{
	long	num;
	int		multiplier;

	num = 0;
	multiplier = 1;
	while (**str == '\n' || **str == '\t' || **str == '\v' ||
			**str == ' ' || **str == '\f' || **str == '\r')
		(*str)++;
	if (**str == '-')
		multiplier = -1;
	if (**str == '+' || **str == '-')
		(*str)++;
	while (**str && **str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num * multiplier);
}

int		ptr_atoi2(char *str, size_t *ptr)
{
	long	ans;
	int		multiplier;
	int		i;

	i = 0;
	ans = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||
			str[i] == ' ' || str[i] == '\f' || str[i] == '\r')
		i++;
	multiplier = str[i] == '-' ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - '0';
		i++;
		if (ans < 0)
			return (multiplier < 0 ? 0 : -1);
	}
	*ptr = *ptr + i;
	return ((int)(ans * multiplier));
}
