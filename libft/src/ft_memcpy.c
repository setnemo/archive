/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:15:52 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/02 19:12:19 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	if (!dst && !src)
		return (NULL);
	ptr1 = (unsigned char*)dst;
	ptr2 = (const unsigned char*)src;
	while (n--)
	{
		*ptr1++ = *ptr2++;
	}
	return (dst);
}
