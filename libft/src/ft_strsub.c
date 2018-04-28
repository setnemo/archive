/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:19:06 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/06 13:43:54 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_fresh;

	if (!s)
		return (NULL);
	if (!(str_fresh = ft_strnew(len)))
		return (NULL);
	str_fresh = ft_strncpy(str_fresh, &s[start], len);
	*(str_fresh + len) = '\0';
	return (str_fresh);
}
