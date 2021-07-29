/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	type_b(va_list *ap, t_params *p)
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
	print_number(num, 2, p, &print_bin_pref);
}

void	type_bb(va_list *ap, t_params *p)
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
	print_number(num, 2, p, &print_bin_pref);
}
