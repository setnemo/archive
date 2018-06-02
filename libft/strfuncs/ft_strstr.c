/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:43:05 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 15:43:05 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *big, const char *small)
{
	int		f_pos;
	int		j;

	f_pos = 0;
	if (small[0] == '\0')
		return ((char*)big);
	while (big[f_pos])
	{
		while (big[f_pos] && big[f_pos] != small[0])
			f_pos++;
		if (big[f_pos])
		{
			j = 1;
			while (small[j] && small[j] == big[f_pos + j])
				j++;
			if (small[j] == '\0')
				return ((char*)(big + f_pos));
		}
		else
			return (NULL);
		f_pos++;
	}
	return (NULL);
}
