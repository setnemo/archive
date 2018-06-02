/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 21:51:02 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/21 22:30:27 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	buf;

	i = 0;
	len = ft_strlen(str) - 1;
	while (len > i)
	{
		buf = str[i];
		str[i] = str[len];
		str[len] = buf;
		i++;
		len--;
	}
	return (str);
}
