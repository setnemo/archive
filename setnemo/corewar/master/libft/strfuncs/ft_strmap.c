/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:03:38 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 14:03:38 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		ans[i] = (*f)(*(s + i));
	return (ans);
}
