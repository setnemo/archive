/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_num_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:53:41 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:53:41 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	quick_sort(int *mass, int a, int b)
{
	int		l;
	int		r;
	int		comparer;
	int		c;

	l = a;
	r = b;
	comparer = mass[b];
	while (l <= r)
	{
		while (mass[l] < comparer)
			l++;
		while (mass[r] > comparer)
			r--;
		if (l <= r)
		{
			c = mass[l];
			mass[l] = mass[r];
			mass[r] = c;
		}
	}
	if (a < r)
		quick_sort(mass, a, r);
	if (b > l)
		quick_sort(mass, l, b);
}

void		ft_sort_num_tab(int *mass, int size)
{
	quick_sort(mass, 1, size - 1);
}
