/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:28:56 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/17 20:28:56 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdupab(const char *str, int a, int b)
{
	char	*ans;
	int		strl;
	int		i;
	int		j;
	int		until;

	if (!str || a > b)
		return (ft_strnew(0));
	strl = ft_strlen(str);
	until = b < strl ? b : strl;
	i = a > -1 ? a : 0;
	ans = (char*)malloc(sizeof(char) * (until - i + 2));
	if (!ans)
		return (ans);
	i--;
	j = 0;
	while (++i <= until)
		ans[j++] = str[i];
	ans[j] = '\0';
	return (ans);
}
