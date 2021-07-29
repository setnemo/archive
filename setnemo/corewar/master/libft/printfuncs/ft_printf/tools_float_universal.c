/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_float_universal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:24:20 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/30 16:24:21 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include <float.h>

void		print_e_exp(t_params *p, int expon, char c)
{
	size_t			savelen_exp;

	print_symbol(p, c);
	print_symbol(p, expon < 0 ? '-' : '+');
	expon = expon < 0 ? -expon : expon;
	if (expon == 0)
		print_str(p, "00", 1);
	else if (expon < 10)
	{
		print_symbol(p, '0' + expon / 10);
		print_symbol(p, '0' + expon % 10);
	}
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

static void	print_float_word(t_params *p, char *str)
{
	int	i;

	p->flags->plus = str[0] != 'i' && str[0] != 'I' ? 0 : p->flags->plus;
	p->flags->space = p->flags->minus && (str[0] == 'n' || str[0] == 'N') ?
		0 : p->flags->space;
	if ((p->flags->plus || p->flags->space) && str[0] != '-')
		i = 3;
	else if (str[0] == 'i' || str[0] == 'n' || str[0] == 'I' || str[0] == 'N')
		i = 2;
	else
		i = 3;
	if (p->flags->minus)
	{
		if (str[0] != '-')
			print_sign_pref(p);
		print_str(p, str, 1);
		while (++i < p->width)
			print_symbol(p, ' ');
		return ;
	}
	while (++i < p->width)
		print_symbol(p, ' ');
	if (str[0] != '-')
		print_sign_pref(p);
	print_str(p, str, 1);
}

static int	recogn_naninf(t_params *p, long double num, _Bool is_cap)
{
	if (num != num)
	{
		if (is_cap)
			print_float_word(p, "NAN");
		else
			print_float_word(p, "nan");
		return (1);
	}
	if (num < -LDBL_MAX)
	{
		if (is_cap)
			print_float_word(p, "-INF");
		else
			print_float_word(p, "-inf");
		return (1);
	}
	if (num > LDBL_MAX)
	{
		if (is_cap)
			print_float_word(p, "INF");
		else
			print_float_word(p, "inf");
		return (1);
	}
	return (0);
}

long double	get_float_num(va_list *ap, t_params *p, _Bool is_cap)
{
	long double num;
	t_cheat		cheat_union;

	num = p->length == BL ? va_arg(*ap, long double) : va_arg(*ap, double);
	if (recogn_naninf(p, num, is_cap))
		return (-1.0);
	cheat_union.d = (double)num;
	p->isnegative = cheat_union.str_cheat.cheat_sign;
	num = p->isnegative ? -num : num;
	p->savelen = p->toprint->len;
	return (num);
}

void		float_flags(t_params *p)
{
	int		until;
	int		j;
	size_t	from;
	char	c;

	j = 0;
	until = p->width - (p->toprint->len - p->savelen);
	if (p->flags->minus)
	{
		while (j++ < until)
			print_symbol(p, ' ');
		return ;
	}
	from = p->flags->zero ? p->savelen + p->pref_len : p->savelen;
	c = p->flags->zero ? '0' : ' ';
	rev_str(&p->toprint->str[from],
		&p->toprint->str[p->toprint->len - 1]);
	while (j++ < until)
		print_symbol(p, c);
	rev_str(&p->toprint->str[from],
		&p->toprint->str[p->toprint->len - 1]);
}
