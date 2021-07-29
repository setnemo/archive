/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:19:50 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 17:19:52 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ans;

	ans = (t_list*)malloc(sizeof(t_list));
	if (!ans)
		return (NULL);
	ans->next = NULL;
	if (!content)
	{
		ans->content = NULL;
		ans->content_size = 0;
	}
	else
	{
		ans->content = ft_memalloc(content_size);
		if (!(ans->content))
		{
			free(ans);
			return (NULL);
		}
		ans->content = ft_memcpy(ans->content, content, content_size);
		ans->content_size = content_size;
	}
	return (ans);
}
