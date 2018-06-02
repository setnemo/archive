/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:20:31 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 15:20:31 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, char const *s2, size_t size)
{
	size_t	i;
	size_t	s1len;
	size_t	s2len;
	size_t	ret;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	i = 0;
	while (s1len + i + 1 < size && s2[i])
	{
		s1[s1len + i] = s2[i];
		i++;
	}
	s1[s1len + i] = '\0';
	ret = s2len + (s1len < size ? s1len : size);
	return (ret);
}
