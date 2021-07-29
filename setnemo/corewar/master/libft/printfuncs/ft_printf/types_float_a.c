/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_float_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void	print_a_exp(t_params *p, int expon, char c)
{
	size_t			savelen_exp;

	print_symbol(p, c);
	print_symbol(p, expon < 0 ? '-' : '+');
	expon = expon < 0 ? -expon : expon;
	if (expon == 0)
		print_str(p, "0", 1);
	else
	{
		savelen_exp = p->toprint->len;
		while (expon > 0)
		{
			print_symbol(p, '0' + expon % 10);
			expon /= 10;
		}
		rev_str(&p->toprint->str[savelen_exp],
			&p->toprint->str[p->toprint->len - 1]);
	}
}

static void	print_aba(t_params *p, t_float *f, char c)
{
	size_t	i;

	print_sign_pref(p);
	print_symbol(p, '0');
	print_symbol(p, c);
	print_symbol(p, f->num[0]);
	if ((f->size > 1 && p->precision < 0) || p->precision > 0 || p->flags->hash)
		print_symbol(p, '.');
	i = 0;
	if (p->precision == -1)
		p->precision = f->size - 1;
	while (++i < f->size && p->precision-- > 0)
		print_symbol(p, f->num[i]);
	while (p->precision-- > 0)
		print_symbol(p, '0');
}

void		type_aba(va_list *ap, t_params *p, char *c, _Bool is_cap)
{
	long double		num;
	static t_float	*f = NULL;

	num = get_float_num(ap, p, is_cap);
	if (num < 0.0)
		return ;
	f = !f ? init_t_float(FLOAT_STR_MAX_SIZE) : f;
	float_to_binary(f, num, is_cap, (p->length == BL ? 1 : 0));
	while (f->num[f->size - 1] == '0' && f->size > 1)
		f->size--;
	f->point = 1;
	p->pref_len = p->isnegative || p->flags->plus || p->flags->space ? 1 : 0;
	print_aba(p, f, c[0]);
	print_a_exp(p, f->expon, c[1]);
	float_flags(p);
}
