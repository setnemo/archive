/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_uns.c                                 :+:      :+:    :+:   */
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

char		*ft_itoa_base_uns(uintmax_t value, int base)
{
	char		*ans;
	int			stringsize;

	stringsize = ft_count_digits_uns(value, base);
	ans = (char*)malloc(sizeof(char) * (stringsize + 1));
	convert_number(value, base, ans, stringsize);
	ans[stringsize] = '\0';
	return (ans);
}
