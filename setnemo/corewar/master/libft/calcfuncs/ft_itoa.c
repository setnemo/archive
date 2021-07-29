/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:35:19 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 13:35:19 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	num_of_digits(long l)
{
	int		ans;

	ans = 0;
	if (l == 0)
		return (1);
	while (l > 0)
	{
		ans++;
		l /= 10;
	}
	return (ans);
}

static void	fill_ans(char *ans, long num, int nsize)
{
	int	i;

	i = -1;
	while (++i < nsize)
	{
		ans[nsize - i - 1] = '0' + num % 10;
		num /= 10;
	}
}

char		*ft_itoa(int n)
{
	char	*ans;
	int		nsize;
	long	ln;
	int		bonus;

	ln = n;
	bonus = ln < 0 ? 1 : 0;
	ln = ln < 0 ? -ln : ln;
	nsize = num_of_digits(ln);
	ans = (char*)malloc(sizeof(char) * (nsize + bonus + 1));
	if (!ans)
		return (ans);
	ans[nsize + bonus] = '\0';
	if (bonus > 0)
		ans[0] = '-';
	fill_ans(ans + bonus, ln, nsize);
	return (ans);
}
