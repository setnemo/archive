/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:46:05 by oantonen          #+#    #+#             */
/*   Updated: 2017/12/24 15:03:15 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (unsigned char*)dst;
	ptr2 = (const unsigned char*)src;
	while (n)
	{
		if (*ptr2 != (unsigned char)c)
			*ptr1++ = *ptr2++;
		else
		{
			*ptr1 = *ptr2;
			return (ptr1 + 1);
		}
		n--;
	}
	return (0);
}
