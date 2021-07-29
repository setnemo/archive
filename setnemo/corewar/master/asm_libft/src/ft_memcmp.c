/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:43:44 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/15 12:54:16 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (unsigned char*)s1;
	ptr2 = (const unsigned char*)s2;
	while (n--)
		if (*ptr1++ != *ptr2++)
			return (*--ptr1 - *--ptr2);
	return (0);
}
