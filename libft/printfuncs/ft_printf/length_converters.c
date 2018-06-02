/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:12:26 by nkolosov          #+#    #+#             */
/*   Updated: 2017/12/06 15:12:26 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include <stddef.h>

void		convert_di(va_list *ap, intmax_t *num, t_params *p)
{
	if (p->length == HH)
		*num = (signed char)va_arg(*ap, int);
	else if (p->length == H)
		*num = (short)va_arg(*ap, int);
	else if (p->length == LL)
		*num = va_arg(*ap, long long);
	else if (p->length == L)
		*num = va_arg(*ap, long);
	else if (p->length == J)
		*num = va_arg(*ap, intmax_t);
	else if (p->length == Z)
		*num = va_arg(*ap, size_t);
	else if (p->length == T)
		*num = va_arg(*ap, ptrdiff_t);
	else
		*num = va_arg(*ap, int);
}

static void	convert_ouxbx_t(va_list *ap, uintmax_t *num)
{
	if (sizeof(unsigned char) == sizeof(ptrdiff_t))
		*num = (unsigned char)va_arg(*ap, int);
	else if (sizeof(unsigned short) == sizeof(ptrdiff_t))
		*num = (unsigned short)va_arg(*ap, int);
	else if (sizeof(unsigned long long) == sizeof(ptrdiff_t))
		*num = va_arg(*ap, unsigned long long);
	else if (sizeof(unsigned long int) == sizeof(ptrdiff_t))
		*num = va_arg(*ap, unsigned long int);
	else
		*num = va_arg(*ap, unsigned int);
}

void		convert_ouxbx(va_list *ap, uintmax_t *num, t_params *p)
{
	if (p->length == HH)
		*num = (unsigned char)va_arg(*ap, int);
	else if (p->length == H)
		*num = (unsigned short)va_arg(*ap, int);
	else if (p->length == LL)
		*num = va_arg(*ap, unsigned long long);
	else if (p->length == L)
		*num = va_arg(*ap, unsigned long);
	else if (p->length == J)
		*num = va_arg(*ap, uintmax_t);
	else if (p->length == Z)
		*num = va_arg(*ap, size_t);
	else if (p->length == T)
		convert_ouxbx_t(ap, num);
	else
		*num = va_arg(*ap, unsigned int);
}
