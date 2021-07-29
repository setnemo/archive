/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:48:03 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/15 14:19:44 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*ptr;
	size_t	len;

	ptr = s1;
	len = ft_strlen(s2);
	while (*ptr)
		ptr++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (s1);
}
