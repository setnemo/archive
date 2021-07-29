/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 21:48:41 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/21 14:03:47 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && --n)
	{
		if (*(unsigned char*)s1 == *(unsigned char*)s2)
		{
			s1++;
			s2++;
		}
		else
			break ;
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
