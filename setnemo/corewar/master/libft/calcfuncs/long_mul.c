/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:04:25 by exam              #+#    #+#             */
/*   Updated: 2017/11/21 11:26:18 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#define GN(x) x - '0'
#define GC(x) x + '0'

static char	*insert_num(char *str, int num)
{
	char	*ans;
	int		i;
	int		len;

	len = ft_strlen(str);
	ans = ft_strnew(len + 1);
	i = -1;
	while (++i < len)
		ans[i] = str[i];
	ans[len] = GC(num);
	free(str);
	return (ans);
}

static char	*long_sum(char *s1, char *s2)
{
	char	*ans;
	char	*s;
	char	*p1;
	int		buf;
	int		i;

	p1 = ft_strlen(s1) > ft_strlen(s2) ? s1 : s2;
	ans = ft_strdup(p1);
	s = ft_strnew(ft_strlen(p1));
	s = p1 == s1 ? ft_strcat(s, s2) : ft_strcat(s, s1);
	i = -1;
	buf = 0;
	while (ans[++i])
	{
		ans[i] = s[i] ? GN(ans[i]) + GN(s[i]) + buf : GN(ans[i]) + buf;
		buf = ans[i] / 10;
		ans[i] = GC(ans[i] % 10);
	}
	if (buf != 0)
		ans = insert_num(ans, buf);
	free(s1);
	free(s2);
	free(s);
	return (ans);
}

static char	*multen(char *str, int tens)
{
	char	*ans;
	int		i;
	int		j;
	int		len;

	if (tens <= 0)
		return (str);
	len = ft_strlen(str);
	ans = ft_strnew(len + tens);
	i = -1;
	while (++i < tens)
		ans[i] = '0';
	j = -1;
	while (str[++j])
		ans[i + j] = str[j];
	free(str);
	return (ans);
}

static char	*mul_num(char *s, int m)
{
	char	*ans;
	int		buf;
	int		i;

	ans = ft_strdup(s);
	i = -1;
	buf = 0;
	while (ans[++i])
	{
		ans[i] = GN(ans[i]);
		ans[i] = ans[i] * m + buf;
		buf = ans[i] / 10;
		ans[i] = GC(ans[i] % 10);
	}
	if (buf != 0)
		ans = insert_num(ans, buf);
	return (ans);
}

char		*long_mul(char *ss1, char *ss2)
{
	char	*s1;
	char	*s2;
	char	*ans;
	char	*temp;
	int		i;

	if (!ss1)
		return (ft_strdup(ss2));
	if (!ss2)
		return (ft_strdup(ss1));
	s1 = ft_strrev(ft_strdup(ss1));
	s2 = ft_strrev(ft_strdup(ss2));
	i = -1;
	ans = ft_strnew(0);
	while (s2[++i])
	{
		temp = mul_num(s1, GN(s2[i]));
		temp = multen(temp, i);
		ans = long_sum(ans, temp);
	}
	ft_strrev(ans);
	free(s1);
	free(s2);
	return (ans);
}
