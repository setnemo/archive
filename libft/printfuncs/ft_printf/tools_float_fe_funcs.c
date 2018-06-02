/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_float_fe_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:23:23 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/29 14:23:23 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		type_f(va_list *ap, t_params *p)
{
	type_fbf(ap, p, 0);
}

void		type_bf(va_list *ap, t_params *p)
{
	type_fbf(ap, p, 1);
}

void		type_e(va_list *ap, t_params *p)
{
	type_ebe(ap, p, 'e', 0);
}

void		type_be(va_list *ap, t_params *p)
{
	type_ebe(ap, p, 'E', 1);
}
