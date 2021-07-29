/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:55:03 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 13:55:05 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include <string.h>

static void	small_f(uintmax_t n, int fd, size_t *ret)
{
	if (n >= 10)
	{
		small_f(n / 10, fd, ret);
		*ret = *ret + ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		*ret = *ret + ft_putchar_fd(n % 10 + '0', fd);
}

size_t		ft_putnbr_uns_fd(uintmax_t n, int fd)
{
	size_t	ret;

	ret = 0;
	small_f(n, fd, &ret);
	return (ret);
}
