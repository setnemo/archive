/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:22:01 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 19:22:01 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	if (!s)
		return (NULL);
	s1 = (unsigned char *)s;
	i = 0;
	while (i < n && s1[i])
	{
		if (s1[i] == (unsigned char)c)
			return ((void*)((unsigned char*)s + i));
		i++;
	}
	return (NULL);
}
