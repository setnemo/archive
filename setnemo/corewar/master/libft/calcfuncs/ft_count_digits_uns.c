/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits_uns.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:59:28 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:59:28 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int		ft_count_digits_uns(intmax_t value, int base)
{
	int		ans;

	ans = 0;
	if (value == 0)
		return (1);
	while (value != 0)
	{
		ans++;
		value /= base;
	}
	return (ans);
}
