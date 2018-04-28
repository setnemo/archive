/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 20:23:19 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/27 18:57:28 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char *s2, size_t n)
{
	char	*ptr;

	ptr = s1;
	while (*ptr)
		ptr++;
	while (n-- && *s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (s1);
}
