/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:58:15 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:58:15 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

static char	get_char(int n)
{
	if (n <= 9)
		return (n + '0');
	return (n - 10 + 'a');
}

static void	convert_number(uintmax_t value, int base, char *str, int ssize)
{
	int		i;

	if (value == 0)
	{
		str[0] = '0';
		return ;
	}
	i = ssize - 1;
	while (value > 0)
	{
		str[i] = get_char(value % base);
		value /= base;
		i--;
	}
}

char		*ft_itoa_base(intmax_t value, int base)
{
	char		*ans;
	int			stringsize;
	int			bonus;
	uintmax_t	val;

	stringsize = ft_count_digits(value, base);
	bonus = value < 0 ? 1 : 0;
	ans = (char*)malloc(sizeof(char) * (stringsize + bonus + 1));
	val = value < 0 ? -value : value;
	val += value < 0 && (intmax_t)(value - 1) > 0 ? 1 : 0;
	ans[0] = value < 0 ? '-' : '0';
	convert_number(val, base, ans + bonus, stringsize);
	ans[stringsize + bonus] = '\0';
	return (ans);
}
