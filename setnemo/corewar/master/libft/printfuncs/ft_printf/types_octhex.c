/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_octhex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	type_o(va_list *ap, t_params *p)
{
	uintmax_t	num;

	convert_ouxbx(ap, &num, p);
	p->flags->hash = num == 0 && p->precision != 0 ? 0 : p->flags->hash;
	p->pref_len = p->flags->hash ? 1 : 0;
	p->flags->space = 0;
	p->flags->plus = 0;
	p->isnegative = 0;
	p->precision -= p->precision > 0 ? p->pref_len : 0;
	p->flags->zero = p->precision >= 0 ? 0 : p->flags->zero;
	print_number(num, 8, p, &print_oct_pref);
}

void	type_bo(va_list *ap, t_params *p)
{
	unsigned long	num;

	num = va_arg(*ap, unsigned long);
	p->flags->hash = num == 0 && p->precision != 0 ? 0 : p->flags->hash;
	p->pref_len = p->flags->hash ? 1 : 0;
	p->flags->space = 0;
	p->flags->plus = 0;
	p->isnegative = 0;
	p->precision -= p->precision > 0 ? p->pref_len : 0;
	p->flags->zero = p->precision >= 0 ? 0 : p->flags->zero;
	print_number(num, 8, p, &print_oct_pref);
}

void	type_x(va_list *ap, t_params *p)
{
	uintmax_t	num;

	convert_ouxbx(ap, &num, p);
	p->flags->hash = num == 0 && p->precision != 0 ? 0 : p->flags->hash;
	p->pref_len = p->flags->hash ? 2 : 0;
	p->flags->hash = num == 0 ? 0 : p->flags->hash;
	p->flags->space = 0;
	p->flags->plus = 0;
	p->isnegative = 0;
	p->flags->zero = p->precision >= 0 ? 0 : p->flags->zero;
	print_number(num, 16, p, &print_hex_pref);
}

void	type_bx(va_list *ap, t_params *p)
{
	uintmax_t	num;

	convert_ouxbx(ap, &num, p);
	p->flags->hash = num == 0 && p->precision != 0 ? 0 : p->flags->hash;
	p->pref_len = p->flags->hash ? 2 : 0;
	p->flags->hash = num == 0 ? 0 : p->flags->hash;
	p->flags->space = 0;
	p->flags->plus = 0;
	p->isnegative = 0;
	p->flags->zero = p->precision >= 0 ? 0 : p->flags->zero;
	p->alphabet = NUMBERS_B;
	print_number(num, 16, p, &print_hex_pref);
}
