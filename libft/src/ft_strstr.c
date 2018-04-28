/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:32:55 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/07 16:32:58 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *tofind)
{
	if (!*tofind)
		return ((char*)str);
	while (*str)
	{
		if (*str != *tofind)
			str++;
		else if (ft_memcmp(str, tofind, ft_strlen(tofind)) == 0)
			return ((char*)str);
		else
			str++;
	}
	return (NULL);
}
