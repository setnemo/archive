/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmdupsymb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 20:03:13 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/30 20:03:13 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_rmdupsymb(char *str)
{
	char	*temp;
	char	*ans;
	int		i;
	int		j;

	if (!str)
		return (str);
	temp = ft_strnew(ft_strlen(str));
	i = -1;
	j = 0;
	while (str[++i])
		if (!(ft_memchr(temp, str[i], ft_strlen(temp))))
			temp[j++] = str[i];
	ans = ft_strdup(temp);
	ft_strdel(&temp);
	ft_strdel(&str);
	return (ans);
}
