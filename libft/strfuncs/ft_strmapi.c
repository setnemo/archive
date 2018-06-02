/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:03:42 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 14:03:42 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ans;
	unsigned int	i;

	if (!s)
		return (NULL);
	ans = ft_strnew(ft_strlen((char*)s));
	if (!ans)
		return (NULL);
	i = -1;
	while (s[++i])
		ans[i] = (*f)(i, *(s + i));
	return (ans);
}
