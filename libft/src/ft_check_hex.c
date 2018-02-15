/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 09:55:17 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/27 09:55:17 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_check_hex(char *str)
{
	int	i;

	i = 0;
	str = ft_strtolower(str);
	while (str[i] != 0)
	{
		if ((str[i] >= '0') && (str[i] <= '9'))
			i++;
		else if ((str[i] >= 'a') && (str[i] <= 'f'))
			i++;
		else
			return (0);
	}
	return (1);
}
