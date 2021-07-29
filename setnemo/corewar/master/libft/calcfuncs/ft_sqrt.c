/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:23:30 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:23:30 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_sqrt(long nb)
{
	double	a;
	double	b;
	long	ia;
	long	ib;

	a = 1;
	b = nb;
	if (nb < 0)
		return (0);
	while (((a > b) && (a - b >= 1)) || ((a < b) && (b - a >= 1)))
	{
		a = (a + b) / 2;
		b = nb / a;
	}
	ia = a;
	ib = b;
	if (ia * ia == nb)
		return (ia);
	if (ib * ib == nb)
		return (ib);
	return (0);
}
