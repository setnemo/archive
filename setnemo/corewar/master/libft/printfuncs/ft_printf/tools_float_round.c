/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_float_round.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:24:20 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/30 16:24:21 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include <float.h>

static void	final_round(t_float *f, t_params *p)
{
	int j;

	j = p->precision - 1;
	while (--j >= 0)
	{
		f->num[j + 1] -= '0';
		f->num[j] += f->num[j + 1] / 10;
		f->num[j + 1] %= 10;
		f->num[j + 1] += '0';
	}
}

void		round_float(t_float *f, t_params *p, _Bool expo)
{
	size_t	j;

	p->precision += f->point;
	if ((size_t)p->precision > f->size)
		return ;
	if (FLT_ROUNDS == 1)
	{
		if (!((size_t)p->precision == f->point &&
		(f->point > 2 || f->num[1] == '0')))
			f->num[p->precision - 1] += ((f->num[p->precision] - '0') / 5);
		final_round(f, p);
	}
	else if ((FLT_ROUNDS == 2 && !p->isnegative) ||
		(FLT_ROUNDS == 3 && p->isnegative))
	{
		j = p->precision - 1;
		while (++j < f->size)
			if (f->num[j] != '0')
				break ;
		if (j != f->size && (expo || f->num[1] != '0'))
			f->num[p->precision - 1]++;
		final_round(f, p);
	}
}

static void	final_round_g(t_float *f, t_params *p)
{
	int j;

	j = p->precision + 1;
	while (--j >= 0)
	{
		f->num[j + 1] -= '0';
		f->num[j] += f->num[j + 1] / 10;
		f->num[j + 1] %= 10;
		f->num[j + 1] += '0';
	}
}

void		round_float_g(t_float *f, t_params *p, _Bool expo)
{
	size_t	j;
	int		saveprec;

	if (p->precision >= (int)f->size)
		return ;
	saveprec = p->precision;
	p->precision += f->num[1] == '0' ? 1 : 0;
	if (FLT_ROUNDS == 1)
	{
		f->num[p->precision] += ((f->num[p->precision + 1] - '0') / 5);
		final_round_g(f, p);
	}
	else if ((FLT_ROUNDS == 2 && !p->isnegative) ||
		(FLT_ROUNDS == 3 && p->isnegative))
	{
		j = p->precision;
		while (++j < f->size)
			if (f->num[j] != '0')
				break ;
		if (j != f->size && (expo || f->num[1] != '0'))
			f->num[p->precision]++;
		final_round_g(f, p);
	}
	(void)expo;
	p->precision = saveprec;
}
