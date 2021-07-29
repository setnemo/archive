/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_float_a_get_float.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"
#include "../../includes/ft_printf_consts.h"
#include "libft.h"
#include "limits.h"

static void	get_int_str(long double *num, t_str *f)
{
	uintmax_t	ts;
	size_t		i;
	size_t		stepen_dvoiki;

	stepen_dvoiki = 0;
	while (*num > ULLONG_MAX)
	{
		*num /= 2.0;
		stepen_dvoiki++;
	}
	ts = (uintmax_t)*num;
	*num -= ts;
	i = 0;
	if (ts == 0)
		f->str[f->size++] = '0';
	else
		while (ts > 0)
		{
			f->str[f->size++] = ts % 2 + '0';
			ts /= 2;
		}
	rev_str(f->str, &f->str[f->size - 1]);
	while (stepen_dvoiki-- > 0)
		f->str[f->size++] = '0';
}

static void	get_frac_str(long double num_frac, t_str *f)
{
	size_t			i;

	i = -1;
	while (++i < 1001 && num_frac > 0.0)
	{
		num_frac *= 2.0;
		f->str[f->size++] = num_frac >= 1.0 ? '1' : '0';
		if (num_frac >= 1.0)
			num_frac -= 1.0;
	}
}

static int	pre(t_float *f, t_str *dbl, _Bool is_cap, _Bool is_long)
{
	size_t	j;
	size_t	i;
	char	buf[4];

	i = 1;
	if (is_long)
	{
		i += 3;
		j = -1;
		while (++j < 4 && j < dbl->size)
			buf[j] = dbl->str[j];
		while (j < 4)
			buf[j++] = '0';
		f->num[f->size++] = hex_from_dec(buf, is_cap);
		if (dbl->size < 4)
		{
			f->expon -= f->num[0] == '0' ? 1 : i;
			return (-1);
		}
	}
	else if (dbl->str[0] != '0')
		f->num[f->size++] = dbl->str[0];
	return (i);
}

static void	extention(t_str *dbl, t_float *f, size_t i, _Bool is_cap)
{
	size_t			j;
	char			buf[4];
	char			c;

	while (i + 3 < dbl->size)
	{
		buf[0] = dbl->str[i];
		buf[1] = dbl->str[i + 1];
		buf[2] = dbl->str[i + 2];
		buf[3] = dbl->str[i + 3];
		c = hex_from_dec(buf, is_cap);
		if (!(c == '0' && f->size == 0))
			f->num[f->size++] = c;
		i += 4;
	}
	if (f->size == 0 || i != dbl->size)
	{
		j = 0;
		while (i < dbl->size)
			buf[j++] = dbl->str[i++];
		while ((j == 0 && f->size == 0) || (j > 0 && j < 4))
			buf[j++] = '0';
		f->num[f->size++] = hex_from_dec(buf, is_cap);
	}
}

void		float_to_binary(t_float *f, long double num,
							_Bool is_cap, _Bool is_long)
{
	static t_str	*dbl = NULL;
	size_t			i;

	dbl = !dbl ? init_t_str(FLOAT_A_STR_MAX_SIZE) : dbl;
	dbl->size = 0;
	f->size = 0;
	get_int_str(&num, dbl);
	f->expon = dbl->size;
	get_frac_str(num, dbl);
	if ((int)(i = pre(f, dbl, is_cap, is_long)) < 0)
		return ;
	f->expon -= i;
	extention(dbl, f, i, is_cap);
}
