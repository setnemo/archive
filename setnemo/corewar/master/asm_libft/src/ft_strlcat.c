/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 21:57:20 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/27 18:57:17 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strnlen(const char *s, size_t dstsize)
{
	size_t	length;

	if (!s)
		return (0);
	length = ft_strlen(s);
	if (length < dstsize)
		return (length);
	else
		return (dstsize);
}

size_t			ft_strlcat(char *dst, char *src, size_t buf)
{
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	dstlen = ft_strnlen(dst, buf);
	if (dstlen == buf)
		return (buf + srclen);
	if (srclen < buf - dstlen)
		ft_memcpy(dst + dstlen, src, srclen + 1);
	else if (srclen == buf - dstlen)
	{
		ft_memcpy(dst + dstlen, src, srclen);
		dst[dstlen + srclen - 1] = '\0';
	}
	else
	{
		ft_memcpy(dst + dstlen, src, buf - 1 - dstlen);
		dst[buf - 1] = '\0';
	}
	return (dstlen + srclen);
}
