/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:05:02 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 15:05:03 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	first_ws;
	size_t	last_ws;
	char	*ans;
	size_t	i;

	if (!s)
		return (NULL);
	first_ws = 0;
	while (s[first_ws] && (ft_iswhitespace(s[first_ws])))
		first_ws++;
	if (!s[first_ws])
		return (ft_strnew(0));
	last_ws = ft_strlen((char*)s) - 1;
	while (ft_iswhitespace(s[last_ws]))
		last_ws--;
	ans = ft_strnew(last_ws - first_ws + 1);
	if (!ans)
		return (NULL);
	i = first_ws - 1;
	while (++i <= last_ws)
		ans[i - first_ws] = s[i];
	return (ans);
}
