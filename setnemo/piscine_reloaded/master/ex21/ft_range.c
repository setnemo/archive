/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 09:44:23 by apakhomo          #+#    #+#             */
/*   Updated: 2017/10/25 09:44:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int i;
	int *range;

	i = 0;
	if (min < max)
	{
		range = (int*)malloc(sizeof(int) * (max - min) + 1);
		while (min + i < max)
		{
			range[i] = min + i;
			i++;
		}
		range[i] = 0;
		return (range);
	}
	else
	{
		range = NULL;
		return (range);
	}
}
