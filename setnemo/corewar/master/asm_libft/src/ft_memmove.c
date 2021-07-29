/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:59:00 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/23 14:58:48 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (unsigned char*)dst;
	ptr2 = (const unsigned char*)src;
	if (ptr1 > ptr2)
		while (len--)
			*(ptr1 + len) = *(ptr2 + len);
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}
