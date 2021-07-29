/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:55:13 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/21 13:55:13 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

t_read_arr	*read_lines(int fd)
{
	t_read_arr	*arr;
	t_list		*readlist;
	char		*readline;
	char		buf[256];
	int			ret;

	if (fd < 0 || (read(fd, 0, 0)) < 0)
		return (NULL);
	if (!(arr = (t_read_arr*)malloc(sizeof(t_read_arr))))
		return (NULL);
	readline = NULL;
	readlist = NULL;
	while ((ret = read(fd, buf, 256)) > 0)
		ft_lstpushback(&readlist, ft_lstnew((void*)buf, ret));
	if (!readlist)
		return (NULL);
	readline = ft_list_to_string(readlist, NULL);
	ft_lstdel(&readlist, NULL);
	arr->lines = ft_strsplit(readline, '\n');
	arr->size = 0;
	while (arr->lines[arr->size])
		arr->size++;
	free(readline);
	return (arr);
}

void		free_read_lines(t_read_arr *arr)
{
	while (arr->size > 0)
	{
		arr->size--;
		free(arr->lines[arr->size]);
	}
	free(arr->lines);
	free(arr);
}
