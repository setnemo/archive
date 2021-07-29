/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	type_percent(va_list *ap, t_params *p)
{
	int		i;
	char	filler;

	(void)ap;
	p->width--;
	i = -1;
	filler = p->flags->zero ? '0' : ' ';
	if (p->flags->minus)
	{
		print_symbol(p, '%');
		while (++i < p->width)
			print_symbol(p, ' ');
		return ;
	}
	while (++i < p->width)
		print_symbol(p, filler);
	print_symbol(p, '%');
}

void	type_p(va_list *ap, t_params *p)
{
	uintmax_t	num;

	num = va_arg(*ap, uintmax_t);
	p->flags->hash = 1;
	p->pref_len = 2;
	print_number(num, 16, p, &print_hex_pref);
}

void	type_n(va_list *ap, t_params *p)
{
	if (p->length == HH)
		*(va_arg(*ap, signed char*)) = (signed char)p->toprint->len;
	else if (p->length == H)
		*(va_arg(*ap, short*)) = (short)p->toprint->len;
	else if (p->length == LL)
		*(va_arg(*ap, long long*)) = (long long)p->toprint->len;
	else if (p->length == L)
		*(va_arg(*ap, long*)) = (long)p->toprint->len;
	else if (p->length == J)
		*(va_arg(*ap, intmax_t*)) = (intmax_t)p->toprint->len;
	else if (p->length == Z)
		*(va_arg(*ap, size_t*)) = (size_t)p->toprint->len;
	else
		*(va_arg(*ap, int*)) = (int)p->toprint->len;
}

void	type_none(char c, t_params *p)
{
	int		i;
	char	filler;

	p->width--;
	i = -1;
	filler = p->flags->zero ? '0' : ' ';
	if (p->flags->minus)
	{
		print_symbol(p, c);
		while (++i < p->width)
			print_symbol(p, ' ');
		return ;
	}
	while (++i < p->width)
		print_symbol(p, filler);
	print_symbol(p, c);
}
