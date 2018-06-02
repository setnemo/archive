/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:21:41 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 16:21:41 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		f_pos;
	char	cc;

	cc = (char)c;
	f_pos = ft_strlen((char*)s);
	if (cc == '\0')
		return ((char*)(s + f_pos));
	f_pos--;
	while (f_pos >= 0)
	{
		if (s[f_pos] == cc)
			return ((char*)(s + f_pos));
		f_pos--;
	}
	return (NULL);
}
