/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:11:33 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/17 20:04:25 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	if (!*find)
		return ((char*)str);
	while (*str && len--)
	{
		if (*str == *find && ft_strlen(find) <= len + 1)
		{
			if (ft_memcmp(str, find, ft_strlen(find)) == 0)
				return ((char*)str);
			else
				str++;
		}
		else
			str++;
	}
	return (NULL);
}
