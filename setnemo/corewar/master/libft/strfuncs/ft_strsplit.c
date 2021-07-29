/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:05:11 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/27 15:05:11 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_num_of_words(char const *s, char c)
{
	int		ans;
	int		i;

	i = 0;
	ans = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			ans++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (ans);
}

static char	*get_next_word(char const *s, int *pos, char c)
{
	int		i;
	char	*ans;

	i = 0;
	while (s[*pos + i] && s[*pos + i] != c)
		i++;
	ans = ft_strnew(i);
	if (!ans)
		return (NULL);
	i = 0;
	while (s[*pos + i] && s[*pos + i] != c)
	{
		ans[i] = s[*pos + i];
		i++;
	}
	ans[i] = '\0';
	*pos = *pos + i;
	return (ans);
}

static void	second_part(char const *s, char **ans, int nofw, char c)
{
	int		nw;
	int		i;

	i = 0;
	nw = 0;
	while (nw != nofw)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			ans[nw] = get_next_word(s, &i, c);
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

char		**ft_strsplit(char const *s, char c)
{
	char	**ans;
	int		num_of_words;

	if (!s)
		return (NULL);
	num_of_words = count_num_of_words(s, c);
	ans = (char**)malloc(sizeof(char*) * (num_of_words + 1));
	if (!ans)
		return (NULL);
	second_part(s, ans, num_of_words, c);
	ans[num_of_words] = NULL;
	return (ans);
}

void		free_word_arr(char **words)
{
	int i;

	i = -1;
	while (words[++i])
		free(words[i]);
	free(words);
}
