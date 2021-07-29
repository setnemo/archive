/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/ft_printf.h"
#include "../../includes/ft_printf_funcs.h"
#include <unistd.h>

static void	get_numbered_args(t_params *p, va_list *ap, va_list *begin)
{
	if (p->is_width_subst)
	{
		va_end(*ap);
		va_copy(*ap, *begin);
		while (--p->width > 0)
			va_arg(*ap, size_t);
		p->width = va_arg(*ap, int);
	}
	if (p->is_precision_subst)
	{
		va_end(*ap);
		va_copy(*ap, *begin);
		while (--p->precision > 0)
			va_arg(*ap, size_t);
		p->precision = va_arg(*ap, int);
	}
	if (p->n-- > 0)
	{
		va_end(*ap);
		va_copy(*ap, *begin);
		while (p->n-- > 0)
			va_arg(*ap, size_t);
	}
}

static void	call_mathing_func(size_t *j, char fmt_i, va_list *ap, t_params *p)
{
	while (++(*j) < NOFFUNCS)
		if (fmt_i == g_type_funcs[*j].c)
		{
			g_type_funcs[*j].func(ap, p);
			break ;
		}
}

static void	run_while(va_list *ap, const char *fmt, t_params *p)
{
	size_t			j;
	size_t			i;
	va_list			begin;

	va_copy(begin, *ap);
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			read_params(p, (char*)fmt, &i, ap);
			if (!fmt[i])
				continue ;
			get_numbered_args(p, ap, &begin);
			j = -1;
			call_mathing_func(&j, fmt[i], ap, p);
			if (j == NOFFUNCS)
				type_none(fmt[i], p);
		}
		else
			print_symbol(p, fmt[i]);
		i++;
	}
}

int			ft_printf(const char *fmt, ...)
{
	va_list			ap;
	static t_params	*p = NULL;

	p = p ? p : init_params();
	p->toprint->len = 0;
	if (!fmt)
		return (-1);
	va_start(ap, fmt);
	run_while(&ap, fmt, p);
	va_end(ap);
	write(1, p->toprint->str, p->toprint->len);
	return (p->toprint->len);
}
