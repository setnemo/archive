/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_float_g.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include <float.h>

static void	check_expon_extra(t_params *p, t_float *f, int *expon, int j)
{
	if (FLT_ROUNDS == 1)
	{
		while (++j <= p->precision)
			if (f->num[j] != '9')
				break ;
		if (j > p->precision)
			if (f->num[j] >= '5')
				(*expon)++;
	}
	else if ((FLT_ROUNDS == 2 && !p->isnegative) ||
			(FLT_ROUNDS == 3 && p->isnegative))
	{
		j = 1;
		while (j <= p->precision && j < (int)f->size)
			if (f->num[j++] != '9')
				break ;
		if (j-- > p->precision && !(p->precision == 1 && f->num[1] != '9'))
		{
			while (++j < (int)f->size)
				if (f->num[j] != '0')
					break ;
			if (j != (int)f->size)
				(*expon)++;
		}
	}
}

static void	print_e_prep(t_params *p, t_float *f, int first_prec)
{
	f->point = 1;
	while (f->num[f->point - 1] == '0')
		f->point++;
	f->point = f->num[f->point - 1] ? f->point : 2;
	p->precision--;
	round_float(f, p, 1);
	if (f->num[0] != '0')
		f->point--;
	p->precision = first_prec;
	p->precision = p->precision == 0 ? 1 : p->precision;
	p->precision = p->precision == -1 ? 6 : p->precision;
	print_symbol(p, f->num[f->point - 1]);
	p->precision--;
	if (!p->flags->hash)
		while (f->num[f->point + p->precision - 1] == '0')
			p->precision--;
	while (f->num[f->size - 1] == '0')
		f->size--;
}

static void	print_e(t_params *p, t_float *f, char c, int first_prec)
{
	size_t	i;

	print_e_prep(p, f, first_prec);
	i = f->point - 1;
	if (p->flags->hash || (p->precision > 0 && f->size > f->point))
		print_symbol(p, '.');
	while (p->precision > 0 && ++i < f->size)
	{
		print_symbol(p, f->num[i]);
		p->precision--;
	}
	if (p->flags->hash)
		while (p->precision-- > 0)
			print_symbol(p, '0');
	print_e_exp(p, f->expon, c);
}

static void	print_f(t_params *p, t_float *f)
{
	size_t	i;

	round_float_g(f, p, 0);
	i = f->num[0] == '0' && f->point > 1 ? 0 : -1;
	while (++i < f->point && p->precision--)
		print_symbol(p, f->num[i]);
	i--;
	while (f->num[f->size - 1] == '0')
		f->size--;
	if (i == 1 && f->num[1] == '0' && f->size != 0)
		p->precision++;
	if (!p->flags->hash)
		while (f->num[f->point + p->precision - 1] == '0')
			p->precision--;
	if (p->flags->hash || (p->precision > 0 && f->size > f->point))
		print_symbol(p, '.');
	while (p->precision > 0 && ++i < f->size)
	{
		print_symbol(p, f->num[i]);
		p->precision--;
	}
	if (p->flags->hash)
		while (p->precision-- > 0)
			print_symbol(p, '0');
}

void		type_gbg(va_list *ap, t_params *p, char c, _Bool is_cap)
{
	long double		num;
	size_t			i;
	int				first_prec;
	static t_float	*f = NULL;

	first_prec = p->precision;
	num = get_float_num(ap, p, is_cap);
	p->precision = p->precision == 0 ? 1 : p->precision;
	p->precision = p->precision < 0 ? 6 : p->precision;
	if (num < 0.0)
		return ;
	f = !f ? init_t_float(FLOAT_STR_MAX_SIZE) : f;
	set_float(f, num);
	i = 0;
	while (f->num[i] == '0')
		i++;
	i = f->size == i ? 1 : i;
	f->expon = f->point - i - 1;
	check_expon_extra(p, f, &f->expon, 0);
	print_sign_pref(p);
	if (f->expon < -4 || f->expon >= p->precision)
		print_e(p, f, c, first_prec);
	else
		print_f(p, f);
	float_flags(p);
}
