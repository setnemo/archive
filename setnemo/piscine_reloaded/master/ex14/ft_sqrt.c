/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:08:37 by apakhomo          #+#    #+#             */
/*   Updated: 2017/10/24 11:08:38 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int temp;

	if (nb < 1)
		return (0);
	else
	{
		temp = 1;
		while (temp * temp < nb)
			temp++;
		if (temp * temp == nb)
			return (temp);
		else
			return (0);
	}
}
