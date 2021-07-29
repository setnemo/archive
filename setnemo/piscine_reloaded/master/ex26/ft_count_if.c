/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 09:57:28 by apakhomo          #+#    #+#             */
/*   Updated: 2017/10/25 09:57:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_if(char **tab, int (*f)(char*))
{
	int a;
	int b;

	a = 0;
	b = 0;
	while (tab[a] != '\0')
	{
		if (f(tab[a]) == 1)
			b++;
		a++;
	}
	return (b);
}
