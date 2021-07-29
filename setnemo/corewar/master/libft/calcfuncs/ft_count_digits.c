/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:59:28 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:59:28 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int		ft_count_digits(intmax_t value, int base)
{
	intmax_t	temp;
	int			ans;

	temp = value < 0 ? -value : value;
	ans = 0;
	if (temp == 0)
		return (1);
	while (temp != 0)
	{
		ans++;
		temp /= base;
	}
	return (ans);
}
