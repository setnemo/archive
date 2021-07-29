/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:12:26 by nkolosov          #+#    #+#             */
/*   Updated: 2017/12/06 15:12:26 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	print_sign_pref(t_params *p)
{
	if (p->isnegative)
		print_symbol(p, '-');
	else if (p->flags->plus)
		print_symbol(p, '+');
	else if (p->flags->space)
		print_symbol(p, ' ');
}

void	print_oct_pref(t_params *p)
{
	if (p->flags->hash)
		print_symbol(p, '0');
}

void	print_hex_pref(t_params *p)
{
	if (!p->flags->hash)
		return ;
	print_symbol(p, p->alphabet[10] == 'a' ? 'x' : 'X');
	print_symbol(p, '0');
}

void	print_bin_pref(t_params *p)
{
	if (!p->flags->hash)
		return ;
	print_symbol(p, p->alphabet[10] == 'a' ? 'b' : 'B');
	print_symbol(p, '0');
}
