/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_mul_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:04:25 by exam              #+#    #+#             */
/*   Updated: 2017/11/21 11:26:18 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_str	*mul_base(t_str *s, int tens)
{
	t_str	*ans;
	size_t	i;

	if (tens <= 0)
		return (s);
	ans = (t_str*)malloc(sizeof(t_str));
	ans->str = ft_strnew(s->size + tens);
	ans->size = s->size + tens;
	i = -1;
	while (++i < s->size)
		ans->str[tens + i] = s->str[i];
	free(s->str);
	free(s);
	return (ans);
}

static t_str	*mul_num(t_str *s, int m, size_t base)
{
	t_str	*ans;
	int		buf;
	size_t	i;

	ans = (t_str*)malloc(sizeof(t_str));
	ans->str = ft_strnew(s->size);
	ans->size = s->size;
	i = -1;
	while (++i < ans->size)
		ans->str[i] = s->str[i];
	i = -1;
	buf = 0;
	while (++i < ans->size)
	{
		buf = ans->str[i] * m + buf;
		ans->str[i] = buf % base;
		buf = buf / base;
	}
	if (buf != 0)
		ans = insert_num_base(ans, buf);
	return (ans);
}

static char		*run_algo(t_str *s1, t_str *s2, t_str *ans, size_t base)
{
	t_str	*temp;
	size_t	i;
	char	c;

	str_to_num(s1);
	str_to_num(s2);
	i = -1;
	while (++i < s2->size)
	{
		temp = mul_num(s1, s2->str[i], base);
		temp = mul_base(temp, i);
		ans = long_sum_base(ans, temp, base);
	}
	i = -1;
	while (++i < ans->size / 2)
	{
		c = ans->str[i];
		ans->str[i] = ans->str[ans->size - i - 1];
		ans->str[ans->size - i - 1] = c;
	}
	i = -1;
	while (++i < ans->size)
		ans->str[i] = CHAR_FROM_NUM(ans->str[i]);
	return (ans->str);
}

char			*long_mul_base(char *ss1, char *ss2, size_t base)
{
	t_str	*s1;
	t_str	*s2;
	t_str	*ans;
	char	*ret;

	if (!ss1)
		return (ft_strdup(ss2));
	if (!ss2)
		return (ft_strdup(ss1));
	s1 = (t_str*)malloc(sizeof(t_str));
	s2 = (t_str*)malloc(sizeof(t_str));
	ans = (t_str*)malloc(sizeof(t_str));
	s1->str = ft_strrev(ft_strdup(ss1));
	s1->size = ft_strlen(ss1);
	s2->str = ft_strrev(ft_strdup(ss2));
	s2->size = ft_strlen(ss2);
	ans->str = ft_strnew(0);
	ans->size = 0;
	ret = run_algo(s1, s2, ans, base);
	free(s1->str);
	free(s2->str);
	free(s1);
	free(s2);
	free(ans);
	return (ret);
}
