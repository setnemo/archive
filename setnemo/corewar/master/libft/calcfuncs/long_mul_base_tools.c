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

t_str		*insert_num_base(t_str *s, char num)
{
	t_str	*ans;
	size_t	i;

	ans = (t_str*)malloc(sizeof(t_str));
	ans->str = ft_strnew(s->size + 1);
	ans->size = s->size + 1;
	i = -1;
	while (++i < s->size)
		ans->str[i] = s->str[i];
	ans->str[s->size] = num;
	free(s->str);
	free(s);
	return (ans);
}

static void	mini(t_str *ans, t_str *s, size_t base)
{
	size_t	i;
	int		buf;

	i = -1;
	buf = 0;
	while (++i < ans->size)
	{
		buf = i < s->size ? ans->str[i] + s->str[i] + buf : ans->str[i] + buf;
		ans->str[i] = buf % base;
		buf = buf / base;
	}
	if (buf != 0)
		ans = insert_num_base(ans, buf);
}

static void	free_strs(t_str *s1, t_str *s2, t_str *s)
{
	free(s1->str);
	free(s1);
	free(s2->str);
	free(s2);
	free(s->str);
	free(s);
}

t_str		*long_sum_base(t_str *s1, t_str *s2, size_t base)
{
	t_str	*ans;
	t_str	*s;
	t_str	*p1;
	t_str	*p2;
	size_t	i;

	p1 = s1->size > s2->size ? s1 : s2;
	p2 = p1 == s1 ? s2 : s1;
	ans = (t_str*)malloc(sizeof(t_str));
	ans->str = ft_strnew(p1->size);
	ans->size = p1->size;
	i = -1;
	while (++i < p1->size)
		ans->str[i] = p1->str[i];
	s = (t_str*)malloc(sizeof(t_str));
	s->str = ft_strnew(p1->size);
	s->size = p1->size;
	i = -1;
	while (++i < p2->size)
		s->str[i] = p2->str[i];
	mini(ans, s, base);
	free_strs(s1, s2, s);
	return (ans);
}

void		str_to_num(t_str *s)
{
	size_t	i;

	i = -1;
	while (++i < s->size)
		s->str[i] = NUM_FROM_CHAR(s->str[i]);
}
