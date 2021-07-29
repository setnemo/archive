/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:16:19 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:16:20 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_factorial(size_t num)
{
	size_t		ans;
	size_t		prev;
	size_t		i;

	if (num == 0)
		return (1);
	ans = 1;
	prev = 1;
	i = 0;
	while (++i <= num)
	{
		ans *= i;
		if (ans / i != prev)
			return (0);
		prev = ans;
	}
	return (ans);
}
