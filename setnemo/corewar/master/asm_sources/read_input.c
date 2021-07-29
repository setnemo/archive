/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:32:17 by oantonen          #+#    #+#             */
/*   Updated: 2018/05/06 15:07:53 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

int		check_empty(char *str)
{
	char	*hash;

	hash = NULL;
	hash = ft_strchr(str, '#');
	if (!hash)
		hash = ft_strchr(str, ';');
	if (hash)
		*hash = '\0';
	while (*str)
	{
		if (!ft_strchr(" \t", *str))
			return (0);
		str++;
	}
	return (1);
}

void	save_instruction(t_fls *file, int fd)
{
	char	*first;
	int		i;

	i = 0;
	while (get_next_line(fd, &first) > 0)
	{
		file->line++;
		if (!check_empty(first) && first[0] != '\0')
			ft_list_push_back(&file->instr, ft_lstnew(ft_strtrim(first), \
				file->line));
		ft_strdel(&first);
		i++;
	}
	if (i == 0 || !file->instr)
		print_errors2(0, "No instruction was found", "END", file->line);
	if (!g_is_err)
		split_lines(file, file->instr);
	if (!g_is_err)
		split_labels(file, file->instr);
}

void	save_header(t_fls *file, int fd)
{
	int		i;
	char	*s;
	char	*p;

	i = 0;
	while (i != 4 && get_next_line(fd, &s) > 0)
	{
		p = s;
		while (*p)
		{
			if (*p == '"')
				i++;
			p++;
		}
		ft_list_push_back(&(file->lines), ft_lstnew(s, 0));
		file->line++;
	}
	if (i != 4)
	{
		if (file->line == 0)
			file->line++;
		print_errors2(1, "[TOKEN]", "incomplete header structure", file->line);
	}
}

int		save_file(t_list **fl_lst, t_list **fl_err, int fd)
{
	t_fls	*file;

	file = (t_fls*)malloc(sizeof(t_fls));
	g_is_err = 0;
	*file = (t_fls){0, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0};
	save_header(file, fd);
	if (g_is_err == 0)
		check_header(file);
	if (g_is_err == 0)
		save_instruction(file, fd);
	if (g_is_err == 0)
		check_instructions(file->spltd, file->lbls);
	if (g_is_err == 0)
	{
		ft_lstadd(fl_lst, ft_lstnew(file, 0));
		return (1);
	}
	ft_lstadd(fl_err, ft_lstnew(file, 0));
	return (0);
}
