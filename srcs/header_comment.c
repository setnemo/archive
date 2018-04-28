/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:36:59 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/27 16:57:35 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

void	inspect_str(char *s, char *chars, int *ii)
{
	int		i;
	char	*c;

	i = 0;
	c = NULL;
	while (s[i])
	{
		if (s[i] == '#')
			return ;
		if (!ft_strchr(chars, s[i]))
		{
			c = ft_strsub(&s[i], 0, 1);
			print_errors2(3, "unexpected symbol", c, *ii);
		}
		i++;
	}
}

void	write_cmnt(t_fls *file, char *src, int *ii, int len_d)
{
	int		len_s;

	if (g_is_err)
		return ;
	len_s = ft_strlen(src);
	if (ft_strchr(src, '\"'))
		len_s = ft_strchr(src, '\"') - src;
	if (len_s + len_d <= COMMENT_LENGTH && ft_strchr(src, '\"'))
	{
		ft_strncat(file->cmnt, src, len_s);
		file->iscmnt = 1;
		inspect_str(&src[++len_s], " \t", ii);
	}
	else if (len_s + len_d < COMMENT_LENGTH && !ft_strchr(src, '\"'))
	{
		ft_strncat(file->cmnt, src, len_s);
		ft_strcat(file->cmnt, "\n");
	}
	else
		print_errors2(1, "COMMENT", "comment length exceeded, max 2048", *ii);
}

void	save_cmnt(t_fls *file, t_list **ptr, char *str, int *i)
{
	char	*c;

	if (!ft_strchr(str, '"'))
		print_errors2(1, "COMMENT", "comment not found", *i);
	file->cmnt = (char*)ft_memalloc(COMMENT_LENGTH + 1);
	while (*str != '"' && !g_is_err)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else
			print_errors2(5, "unexpected symbol", c = ft_strsub(str, 0, 1), *i);
	}
	write_cmnt(file, str + 1, i, (int)ft_strlen(file->cmnt));
	if (file->iscmnt == 0 && !g_is_err)
		*ptr = (*ptr)->next;
	if (file->iscmnt == 0 && !g_is_err)
		while (*ptr && !g_is_err)
		{
			str = (char*)(*ptr)->content;
			if (file->iscmnt == 0)
				write_cmnt(file, str, i, (int)ft_strlen(file->cmnt));
			if (ft_strchr(str, '"'))
				break ;
			*ptr = (*ptr)->next;
		}
}

void	check_cmnt(t_fls *file, t_list **ptr, int *i)
{
	char	*str;

	if (file->iscmnt)
		print_errors2(1, "COMMENT", "duplicated comment", *i);
	str = (char*)(*ptr)->content;
	while (*str && !g_is_err)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else if (*str == '#')
			return ;
		else if (*str == '.' && !strncmp(str, COMMENT_CMD_STRING, 8))
		{
			save_cmnt(file, ptr, str + 8, i);
			return ;
		}
		else
		{
			str = ft_strsub(str, 0, 1);
			print_errors2(5, "unexpected symbol", str, *i);
		}
	}
}
