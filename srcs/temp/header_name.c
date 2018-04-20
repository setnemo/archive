/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 21:20:48 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/31 17:27:12 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

bool	write_name(t_fls *file, char *src, char *dst, int len) //без открывающей кавычки
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '"')
	{
		if (len == PROG_NAME_LENGTH)
			print_errors(18);
		dst[i] = src[len];
		i++;
		len++;
	}
	if (len == PROG_NAME_LENGTH && src[i] == '\0')
		print_errors(18);
	if (src[i] == '\0')
		dst[len] = '\n';
	if (src[i] == '"')
	{
		// ft_printf("srav2=%s\n", src);
		file->isname = 1;
		rotate_str(&src[++i], " \t");
	}
	return (EXIT_SUCCESS);
}

void	save_name(t_fls *file, t_list **ptr, char *str)
{
	if (!ft_strchr(str, '"'))
		print_errors(16);
	file->name = (char*)ft_memalloc(129);
	while (*str != '"')
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else
			print_errors(17);
	}
	write_name(file, str + 1, file->name, (int)ft_strlen(file->name));
	if (file->isname == 0)
		*ptr = (*ptr)->next;
	if (file->isname == 0)
		while (*ptr)//проверить экспериментально птр - НУЛЛ
		{
			str = (char*)(*ptr)->content;
			if (file->isname == 0)
				write_name(file, str, file->name, (int)ft_strlen(file->name));
			if (ft_strchr(str, '"'))
				break;
			*ptr = (*ptr)->next;
		}
	ft_printf("%s\n", file->name);
}

void	check_name(t_fls *file, t_list **ptr)
{
	char	*str;

	if (file->isname)
		print_errors(14);
	str = (char*)(*ptr)->content;
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else if (*str == '#')
			return ;
		else if (*str == '.' && !strncmp(str, NAME_CMD_STRING, 5))
		{
			// ft_printf("%s\n", str);
			save_name(file, ptr, str + 5);
			return ;
		}
		else
			print_errors(15);
	}
}

void	check_hstr(t_fls *file, char *str)
{
	while (*str)
	{
		if (*str == '#')
			return ;
		if (!ft_strchr(" \t\n", *str)) // "
			print_errors(13);
		str++;
	}
}

bool	check_header(t_fls *file)
{
	t_list	*ptr;

	ptr = file->lines;
	while (ptr)
	{
		// ft_printf("ptr2=%s\n", (char*)ptr->content);
		if (ft_strstr((char*)ptr->content, NAME_CMD_STRING))
		{
			// ft_printf("ptr1=%s\n", (char*)ptr->content);
			check_name(file, &ptr);
			// ft_printf("ptr2=%s\n", (char*)ptr->content);
		}
		else if (ft_strstr((char*)ptr->content, COMMENT_CMD_STRING))
		{
			check_cmnt(file, &ptr);
		}
		else
			check_hstr(file, (char*)ptr->content);
		ptr = ptr->next;
	}
	return (1);
}