/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrendl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:11:39 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 17:11:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include <string.h>

size_t		ft_putnbrendl(intmax_t n)
{
	size_t	ret;

	ret = ft_putnbr(n);
	ft_putchar('\n');
	return (ret + 1);
}
