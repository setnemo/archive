/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_float_struct_managing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:24:20 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/30 16:24:21 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "libft.h"
#include <stdlib.h>

t_float		*init_t_float(size_t size)
{
	t_float	*f;

	f = (t_float*)malloc(sizeof(t_float));
	f->num = (char*)malloc(sizeof(char) * (size + 1));
	f->size = 0;
	f->point = -1;
	return (f);
}

t_str		*init_t_str(size_t size)
{
	t_str	*tstr;

	tstr = (t_str*)malloc(sizeof(t_str));
	tstr->str = ft_strnew(size + 1);
	tstr->str[size] = '\0';
	tstr->size = size;
	return (tstr);
}

void		realloc_toprint(t_print_str *tp)
{
	char	*new;
	size_t	i;

	new = (char*)malloc(sizeof(char) * (tp->size * 2 + 1));
	i = -1;
	while (++i < tp->len)
		new[i] = tp->str[i];
	tp->str[tp->len] = '\0';
	free(tp->str);
	tp->str = new;
	tp->size *= 2;
}

void		realloc_t_str(t_str *tstr)
{
	free(tstr->str);
	tstr->str = ft_strnew(tstr->size * 2 + 1);
	tstr->size = tstr->size * 2;
}
