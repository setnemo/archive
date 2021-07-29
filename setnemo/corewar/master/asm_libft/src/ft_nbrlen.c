/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 20:33:17 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/21 21:00:51 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_nbrlen(long long int value)
{
	int len;

	len = 0;
	if (value == 0)
		return (1);
	if (value < 0)
	{
		len++;
		value = -value;
	}
	while (value != 0)
	{
		value = value / 10;
		len++;
	}
	return (len);
}
