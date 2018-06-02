/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:55:25 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 14:55:26 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	sub = ft_strnew(len);
	if (!sub)
		return (NULL);
	i = -1;
	if (!s)
		return (NULL);
	while (++i < (int)len)
		sub[i] = s[start + i];
	return (sub);
}
