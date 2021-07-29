/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:51:11 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/18 21:54:56 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*free_array(char **s)
{
	while (s != NULL)
	{
		free(*s);
		s++;
	}
	return (NULL);
}

static	int		word_count(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (i);
}

static	int		w_length(const char *s, char c)
{
	int	length;

	length = 0;
	while (*s != c && *s)
	{
		length++;
		s++;
	}
	return (length);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str_fresh;
	int		i;

	if (!s)
		return (NULL);
	i = word_count((char*)s, c);
	if (!(str_fresh = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	str_fresh[i] = NULL;
	i = 0;
	while (*s)
	{
		if (*s++ == c)
			;
		else
		{
			str_fresh[i] = ft_strsub(s - 1, 0, w_length(s - 1, c));
			if (!str_fresh[i])
				return (free_array(str_fresh));
			i++;
			s = s + w_length(s - 1, c) - 1;
		}
	}
	return (str_fresh);
}
