/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_word_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:29:06 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:29:06 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	quick_sort(char **mass, int a, int b)
{
	int		l;
	int		r;
	char	*comparer;
	char	*c;

	l = a;
	r = b;
	comparer = mass[b];
	while (l <= r)
	{
		while (ft_strcmp(mass[l], comparer) < 0)
			l++;
		while (ft_strcmp(mass[r], comparer) > 0)
			r--;
		if (l <= r)
		{
			c = mass[l];
			mass[l++] = mass[r];
			mass[r--] = c;
		}
	}
	if (a < r)
		quick_sort(mass, a, r);
	if (b > l)
		quick_sort(mass, l, b);
}

void		ft_sort_word_tab(char **mass)
{
	int	now;

	now = 0;
	while (mass[now])
		now++;
	quick_sort(mass, 1, now - 1);
}
