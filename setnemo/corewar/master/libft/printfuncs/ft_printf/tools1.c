/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:24:20 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/30 16:24:21 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

intmax_t	printf_atoi(char *str, int *p)
{
	uintmax_t	ans;
	int			sign;
	int			i;

	i = 0;
	ans = 0;
	sign = str[i] == '-' ? -1 : 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - '0';
		i++;
	}
	*p = *p + i;
	return (ans * sign);
}

void		rev_str(char *from, char *until)
{
	char	c;

	while (from < until)
	{
		c = *from;
		*from = *until;
		*until = c;
		from++;
		until--;
	}
}

size_t		get_next_length(char *str, t_length *l)
{
	if (str[0] == 'h')
		if (str[1] == 'h')
			*l = *l < HH ? HH : *l;
		else
			*l = *l < H ? H : *l;
	else if (str[0] == 'l')
		if (str[1] == 'l')
			*l = *l < LL ? LL : *l;
		else
			*l = *l < L ? L : *l;
	else if (str[0] == 'j')
		*l = *l < J ? J : *l;
	else if (str[0] == 'z')
		*l = *l < Z ? Z : *l;
	else if (str[0] == 'L')
		*l = *l < BL ? BL : *l;
	else if (str[0] == 't')
		*l = *l < T ? T : *l;
	else
		return (0);
	return (*l == HH || *l == LL ? 2 : 1);
}
