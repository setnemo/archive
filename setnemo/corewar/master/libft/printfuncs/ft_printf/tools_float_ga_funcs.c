/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_float_ga_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		type_a(va_list *ap, t_params *p)
{
	p->alphabet = NUMBERS_S;
	type_aba(ap, p, "xp", 0);
}

void		type_ba(va_list *ap, t_params *p)
{
	p->alphabet = NUMBERS_B;
	type_aba(ap, p, "XP", 1);
}

void		type_g(va_list *ap, t_params *p)
{
	type_gbg(ap, p, 'e', 0);
}

void		type_bg(va_list *ap, t_params *p)
{
	type_gbg(ap, p, 'E', 1);
}
