/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:08:22 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:08:22 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_num_of_words(char const *s)
{
	int		ans;
	int		i;

	i = 0;
	ans = 0;
	while (s[i])
	{
		while (s[i] && ft_iswhitespace(s[i]))
			i++;
		if (s[i])
		{
			ans++;
			while (s[i] && !(ft_iswhitespace(s[i])))
				i++;
		}
	}
	return (ans);
}

static char	*get_next_word(char const *s, int *pos)
{
	int		i;
	char	*ans;

	i = 0;
	while (s[*pos + i] && !(ft_iswhitespace(s[*pos + i])))
		i++;
	ans = ft_strnew(i);
	if (!ans)
		return (NULL);
	i = 0;
	while (s[*pos + i] && !(ft_iswhitespace(s[*pos + i])))
	{
		ans[i] = s[*pos + i];
		i++;
	}
	ans[i] = '\0';
	*pos = *pos + i;
	return (ans);
}

static void	second_part(char const *s, char **ans, int nofw)
{
	int		nw;
	int		i;

	i = 0;
	nw = 0;
	while (nw != nofw)
	{
		while (s[i] && ft_iswhitespace(s[i]))
			i++;
		if (s[i])
		{
			ans[nw] = get_next_word(s, &i);
			if (!ans[nw])
			{
				while (--nw >= 0)
					free(ans[nw]);
				*ans = NULL;
				return ;
			}
			nw++;
		}
	}
}

char		**ft_split_whitespaces(char *s)
{
	char	**ans;
	int		num_of_words;

	if (!s)
		return (NULL);
	num_of_words = count_num_of_words(s);
	ans = (char**)malloc(sizeof(char*) * (num_of_words + 1));
	if (!ans)
		return (NULL);
	second_part(s, ans, num_of_words);
	ans[num_of_words] = NULL;
	return (ans);
}
