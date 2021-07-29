/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 10:54:22 by apakhomo          #+#    #+#             */
/*   Updated: 2017/10/24 10:54:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int count;

	count = 1;
	if (nb == 0)
		return (1);
	if (nb > 12 || nb < 0)
		return (0);
	if (nb > 0)
	{
		while (nb > 0)
		{
			count = count * nb;
			nb--;
		}
		return (count);
	}
	else
		return (0);
}
