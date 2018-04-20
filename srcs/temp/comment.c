/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:36:59 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/31 17:27:55 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

void	rotate_str(char *s, char *chars)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '#')
			return ;
		if (!ft_strchr(chars, s[i]))
			print_errors(29);
		i++;
	}
}

bool	write_cmnt(t_fls *file, char *src, char *dst, int len) //без открывающей кавычки
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '"')
	{
		if (len == COMMENT_LENGTH)
			print_errors(28);
		dst[len] = src[i];
		i++;
		len++;
	}
	// ft_printf("srav2=%d\n", src[i]);
	if (len == COMMENT_LENGTH && src[i] == '\0')
		print_errors(28);
	if (src[i] == '\0')
		dst[len] = '\n';
	if (src[i] == '"')
	{
		file->iscmnt = 1;
		rotate_str(&src[++i], " \t");
	}
	return (EXIT_SUCCESS);
}

void    save_cmnt(t_fls *file, t_list **ptr, char *str)
{
	if (!ft_strchr(str, '"'))
		print_errors(26);
	file->cmnt = (char*)ft_memalloc(COMMENT_LENGTH + 1);
	while (*str != '"')
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else
			print_errors(27);
	}
	write_cmnt(file, str + 1, file->cmnt, (int)ft_strlen(file->cmnt));
	if (file->iscmnt == 0)
		*ptr = (*ptr)->next;
	if (file->iscmnt == 0)
		while (*ptr)//проверить экспериментально птр - НУЛЛ
		{
			str = (char*)(*ptr)->content;
			if (file->iscmnt == 0)
				write_cmnt(file, str, file->cmnt, (int)ft_strlen(file->cmnt));
			if (ft_strchr(str, '"'))
				break;
			*ptr = (*ptr)->next;
		}
		ft_printf("%s\n", file->cmnt);
}

void	check_cmnt(t_fls *file, t_list **ptr)
{
	char	*str;

	if (file->iscmnt)
		print_errors(24);
	str = (char*)(*ptr)->content;
	while (*str)
	{
		// ft_printf("srav=%d\n", strncmp(str, NAME_CMD_STRING, 5));
		if (*str == ' ' || *str == '\t')
			str++;
		else if (*str == '#')
			return ;
		else if (*str == '.' && !strncmp(str, COMMENT_CMD_STRING, 8))
		{
			// ft_printf("%s\n", str);
			save_cmnt(file, ptr, str + 8);
			return ;
		}
		else
			print_errors(25);
	}

}