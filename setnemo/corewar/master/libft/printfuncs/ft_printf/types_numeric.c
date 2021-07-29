/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	type_di(va_list *ap, t_params *p)
{
	intmax_t	num;
	uintmax_t	n;

	convert_di(ap, &num, p);
	p->pref_len = num < 0 || p->flags->plus || p->flags->space ? 1 : 0;
	n = num < 0 ? -num : num;
	p->flags->zero = p->precision >= 0 ? 0 : p->flags->zero;
	p->isnegative = num < 0 ? 1 : 0;
	print_number(n, 10, p, &print_sign_pref);
}

void	type_bd(va_list *ap, t_params *p)
{
	intmax_t	num;
	uintmax_t	n;

	num = va_arg(*ap, long int);
	p->pref_len = num < 0 || p->flags->plus || p->flags->space ? 1 : 0;
	n = num < 0 ? -num : num;
	p->flags->zero = p->precision >= 0 ? 0 : p->flags->zero;
	p->isnegative = num < 0 ? 1 : 0;
	print_number(n, 10, p, &print_sign_pref);
}

void	type_u(va_list *ap, t_params *p)
{
	uintmax_t	n;

	convert_ouxbx(ap, &n, p);
	p->flags->space = 0;
	p->flags->plus = 0;
	p->pref_len = p->flags->plus ? 1 : 0;
	p->flags->zero = p->precision >= 0 ? 0 : p->flags->zero;
	p->isnegative = 0;
	print_number(n, 10, p, &print_sign_pref);
}

void	type_bu(va_list *ap, t_params *p)
{
	uintmax_t	n;

	n = va_arg(*ap, unsigned long);
	p->flags->space = 0;
	p->flags->plus = 0;
	p->pref_len = p->flags->plus ? 1 : 0;
	p->flags->zero = p->precision >= 0 ? 0 : p->flags->zero;
	p->isnegative = 0;
	print_number(n, 10, p, &print_sign_pref);
}
