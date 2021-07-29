/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:46:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/28 16:51:36 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_new;
	size_t	length;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	length = ft_strlen(s1) + ft_strlen(s2);
	if (!(str_new = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	str_new = ft_strcpy(str_new, s1);
	i = i + ft_strlen(s1);
	while (*s2)
	{
		str_new[i] = *s2++;
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
