/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:24:20 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/30 16:24:21 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	print_symbol(t_params *p, char c)
{
	if (p->toprint->len == p->toprint->size)
		realloc_toprint(p->toprint);
	p->toprint->str[p->toprint->len++] = c;
}

void	print_str(t_params *p, char *str, _Bool ignore_prec)
{
	int	i;

	if (!str)
	{
		print_str(p, "(null)", ignore_prec);
		return ;
	}
	i = 0;
	while ((ignore_prec || p->precision < 0 || i < p->precision) && *str)
	{
		print_symbol(p, *str);
		str++;
		i++;
	}
}
