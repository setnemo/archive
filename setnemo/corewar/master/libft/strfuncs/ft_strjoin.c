/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:01:39 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 15:01:40 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = ft_strnew(ft_strlen((char*)s1) + ft_strlen((char*)s2));
	if (!res)
		return (NULL);
	i = -1;
	j = -1;
	if (s1)
		while (s1[++i])
			res[i] = s1[i];
	if (s2)
		while (s2[++j])
			res[i + j] = s2[j];
	return (res);
}
