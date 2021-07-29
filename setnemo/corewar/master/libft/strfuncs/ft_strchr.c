/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:21:34 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 16:21:34 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int		f_pos;
	char	cc;

	cc = (char)c;
	f_pos = 0;
	while (s[f_pos])
	{
		if (s[f_pos] == cc)
			return ((char*)(s + f_pos));
		f_pos++;
	}
	if (cc == '\0')
		return ((char*)(s + f_pos));
	return (NULL);
}
