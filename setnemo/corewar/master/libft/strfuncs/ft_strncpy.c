/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 12:57:03 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 12:57:03 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, char const *src, size_t len)
{
	size_t		i;

	i = 0;
	if (!src)
		return (dest);
	if (!dest)
		return (NULL);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	i--;
	while (++i < len)
		dest[i] = '\0';
	return (dest);
}
