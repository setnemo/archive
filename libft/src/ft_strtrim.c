/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 21:03:39 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/22 21:02:26 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*str_trimmed;
	size_t			begin;
	size_t			end;

	if (!s)
		return (NULL);
	begin = 0;
	end = ft_strlen(s) - 1;
	while ((s[begin] == ' ' || s[begin] == '\n' || s[begin] == '\t') && *s)
		begin++;
	while ((s[end] == ' ' || s[end] == '\n' || s[end] == '\t') && end + 1 != 0)
		end--;
	if (end + 1 == 0)
		return (ft_strnew(0));
	else if (!(str_trimmed = ft_strnew(end - begin + 1)))
		return (NULL);
	str_trimmed = ft_strncpy(str_trimmed, &s[begin], end - begin + 1);
	return (str_trimmed);
}
