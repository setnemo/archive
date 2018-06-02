/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:08:15 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/20 13:08:15 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static size_t	len_of_malloc(t_list *l)
{
	size_t	i;

	i = 0;
	while (l)
	{
		i += l->content_size;
		l = l->next;
	}
	return (i);
}

char			*ft_list_to_string(t_list *t, size_t *len)
{
	char	*ans;
	char	*str;
	size_t	i;
	size_t	j;

	ans = ft_strnew(len_of_malloc(t));
	i = 0;
	while (t)
	{
		j = -1;
		str = (char*)t->content;
		if (str)
			while (++j < t->content_size)
				ans[i++] = str[j];
		t = t->next;
	}
	if (len)
		*len = i;
	return (ans);
}

char			*ft_list_to_string_x64(t_list *t, size_t *len)
{
	char	*ans;
	char	*str;
	size_t	i;
	size_t	j;
	size_t	l;

	l = len_of_malloc(t);
	ans = ft_strnew(l + l / 64 + 1);
	i = 0;
	while (t)
	{
		j = -1;
		str = (char*)t->content;
		if (str)
			while (++j < t->content_size)
			{
				if ((i + 1) % 65 == 0 && i > 0)
					ans[i++] = '\n';
				ans[i++] = str[j];
			}
		t = t->next;
	}
	ans[i++] = '\n';
	len ? (*len = i) : 1;
	return (ans);
}
