/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_float_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "locale.h"

static void	print_float(t_float *f, t_params *p, struct lconv *loc)
{
	size_t	i;

	p->pref_len = p->isnegative || p->flags->plus || p->flags->space ? 1 : 0;
	print_sign_pref(p);
	i = f->num[0] == '0' && f->point > 1 ? 0 : -1;
	while (++i < f->point)
	{
		if (p->flags->apostrophe && p->toprint->len != p->savelen + p->pref_len
			&& (f->point - i) % 3 == 0)
			print_str(p, loc->thousands_sep, 1);
		print_symbol(p, f->num[i]);
	}
	if (!(!p->flags->hash && f->size == f->point))
	{
		if ((size_t)p->precision != f->point || p->flags->hash)
			print_symbol(p, '.');
		while (i < f->size && i < (size_t)p->precision)
		{
			print_symbol(p, f->num[i]);
			i++;
		}
		i -= 1;
		while (++i < (size_t)p->precision)
			print_symbol(p, '0');
	}
}

void		type_fbf(va_list *ap, t_params *p, _Bool is_cap)
{
	long double		num;
	struct lconv	*loc;
	static t_float	*f = NULL;

	loc = localeconv();
	num = get_float_num(ap, p, is_cap);
	p->precision = p->precision < 0 ? 6 : p->precision;
	if (num < 0.0)
		return ;
	f = !f ? init_t_float(FLOAT_STR_MAX_SIZE) : f;
	set_float(f, num);
	round_float(f, p, 0);
	print_float(f, p, loc);
	float_flags(p);
}
