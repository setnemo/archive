/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 12:35:34 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 12:35:35 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*ans;
	int		strl;
	int		i;

	strl = ft_strlen(str);
	if (!str)
		return (NULL);
	ans = (char*)malloc(sizeof(char) * (strl + 1));
	if (!ans)
		return (ans);
	i = -1;
	while (++i < strl)
		ans[i] = str[i];
	ans[strl] = '\0';
	return (ans);
}
