/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:36:54 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/15 22:30:18 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str_fresh;
	char			*tmp;
	unsigned int	index;

	if (!s)
		return (NULL);
	index = 0;
	if (!(str_fresh = ft_strnew(ft_strlen(s))))
		return (NULL);
	tmp = str_fresh;
	while (*s)
	{
		*tmp++ = f(index++, *s++);
	}
	*tmp = '\0';
	return (str_fresh);
}
