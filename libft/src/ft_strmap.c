/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:02:00 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/16 16:55:07 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str_fresh;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(str_fresh = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[i] != '\0')
	{
		str_fresh[i] = (*f)(s[i]);
		i++;
	}
	str_fresh[i] = '\0';
	return (str_fresh);
}
