/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 17:21:54 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 17:21:54 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;

	s1 = (char*)dst;
	s2 = (char*)src;
	i = -1;
	if (s1 < s2)
		while (++i < len)
			s1[i] = s2[i];
	else
		while (len > 0)
		{
			len--;
			s1[len] = s2[len];
		}
	return (dst);
}
