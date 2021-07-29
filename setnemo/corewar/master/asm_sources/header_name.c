/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 21:20:48 by oantonen          #+#    #+#             */
/*   Updated: 2018/05/06 15:15:30 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

void	write_name(t_fls *file, char *src, int *ii, int len_d)
{
	int		len_s;

	len_s = ft_strlen(src);
	if (g_is_err)
		return ;
	if (ft_strchr(src, '\"'))
		len_s = ft_strchr(src, '\"') - src;
	if (len_s + len_d <= PROG_NAME_LENGTH && ft_strchr(src, '\"'))
	{
		ft_strncat(file->name, src, len_s);
		file->isname = 1;
		inspect_str(&src[++len_s], " \t", ii);
	}
	else if (len_s + len_d < PROG_NAME_LENGTH && !ft_strchr(src, '\"'))
	{
		ft_strncat(file->name, src, len_s);
		ft_strcat(file->name, "\n");
	}
	else
		print_errors2(1, "NAME", "name length exceeded, max 128", *ii);
}

void	save_name(t_fls *file, t_list **ptr, char *str, int *i)
{
	char	*c;

	if (!ft_strchr(str, '\"'))
		print_errors2(1, "NAME", "name not found", *i);
	while (*str != '"' && !g_is_err)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else
			print_errors2(4, "unexpected symbol", c = ft_strsub(str, 0, 1), *i);
	}
	write_name(file, str + 1, i, (int)ft_strlen(file->name));
	if (file->isname == 0)
		*ptr = (*ptr)->next;
	if (file->isname == 0 && !g_is_err)
		while (*ptr)
		{
			str = (char*)(*ptr)->content;
			if (file->isname == 0)
				write_name(file, str, i, (int)ft_strlen(file->name));
			if (ft_strchr(str, '"'))
				break ;
			*ptr = (*ptr)->next;
			i++;
		}
}

void	check_name(t_fls *file, t_list **ptr, int *i)
{
	char	*str;

	if (file->isname)
		print_errors2(1, "[COMMAND_NAME]", ".name", *i);
	str = (char*)(*ptr)->content;
	while (*str && !g_is_err)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else if (*str == COMMENT_CHAR || *str == COMMENT_CHAR2)
			return ;
		else if (*str == '.' && !strncmp(str, NAME_CMD_STRING, 5))
		{
			save_name(file, ptr, str + 5, i);
			return ;
		}
		else
		{
			str = ft_strsub(str, 0, 1);
			print_errors2(4, "unexpected symbol", str, *i);
		}
	}
}

void	check_hstr(char *str, int *i)
{
	char	*c;

	while (*str && !g_is_err)
	{
		if (*str == COMMENT_CHAR || *str == COMMENT_CHAR2)
			return ;
		if (!ft_strchr(" \t\n", *str))
		{
			c = ft_strsub(str, 0, 1);
			print_errors2(3, "unexpected symbol", c, *i);
			ft_strdel(&c);
		}
		str++;
	}
}

void	check_header(t_fls *file)
{
	t_list	*ptr;
	int		i;

	i = 1;
	file->name = (char*)ft_memalloc(PROG_NAME_LENGTH + 1);
	ptr = file->lines;
	while (ptr && !g_is_err)
	{
		if (ft_strstr((char*)ptr->content, NAME_CMD_STRING))
		{
			check_name(file, &ptr, &i);
		}
		else if (ft_strstr((char*)ptr->content, COMMENT_CMD_STRING))
		{
			check_cmnt(file, &ptr, &i);
		}
		else
			check_hstr((char*)ptr->content, &i);
		ptr = ptr->next;
		i++;
	}
}
