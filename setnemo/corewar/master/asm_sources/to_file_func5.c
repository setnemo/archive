/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_file_func5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/04/28 11:49:33 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "op.h"
#define O1 ((x >> 24) & 0xff) | ((x << 8) & 0xff0000)
#define O2 ((x >> 8) & 0xff00) | ((x << 24) & 0xff000000)

int			getwriteargsize(t_asmlst *file_lst, int j)
{
	if (file_lst->bytecode[j] == 1)
		return (1);
	if (file_lst->bytecode[j] == 3)
		return (2);
	if (file_lst->labelsize == 2)
		return (2);
	return (4);
}

void		push_list_to_file(t_asmlst *file_lst, t_asm *data, int asz, int i)
{
	int k;

	while (i < 3)
	{
		if (file_lst->bytecode[i])
		{
			t_byterange.num = 0;
			t_byterange.num = file_lst->value_arg[i];
			asz = getwriteargsize(file_lst, i);
			if (asz == 4)
			{
				k = 5;
				while (--k)
					write(data->dotcorfd, &t_byterange.ch[k - 1], 1);
			}
			if (asz == 2)
			{
				write(data->dotcorfd, &t_byterange.ch2[1], 1);
				write(data->dotcorfd, &t_byterange.ch2[0], 1);
			}
			if (asz == 1)
				write(data->dotcorfd, &file_lst->value_arg[i], 1);
		}
		i++;
	}
}

void		push_name_and_cmnt_to_file(t_asm *data, char buf1[], char buf2[])
{
	int			magic;
	int			x;

	magic = COREWAR_EXEC_MAGIC;
	x = magic;
	x = O1 | O2;
	magic = x;
	x = data->allbytes;
	x = O1 | O2;
	data->allbytes = x;
	write(data->dotcorfd, &magic, 4);
	ft_bzero(buf1, PROG_NAME_LENGTH - ft_strlen(data->filename));
	ft_bzero(buf2, COMMENT_LENGTH - ft_strlen(data->filecomment));
	write(data->dotcorfd, data->filename, ft_strlen(data->filename));
	write(data->dotcorfd, buf1, PROG_NAME_LENGTH - ft_strlen(data->filename));
	write(data->dotcorfd, buf1, 4);
	write(data->dotcorfd, &data->allbytes, 4);
	write(data->dotcorfd, data->filecomment, ft_strlen(data->filecomment));
	write(data->dotcorfd, buf2, COMMENT_LENGTH - ft_strlen(data->filecomment));
	write(data->dotcorfd, buf1, 4);
}

int			push_data_to_file(t_asm *data)
{
	char		buf1[PROG_NAME_LENGTH - ft_strlen(data->filename)];
	char		buf2[COMMENT_LENGTH - ft_strlen(data->filecomment)];
	t_asmlst	*file_lst;

	file_lst = data->next;
	data->dotcorfd = open(data->dotcorname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->dotcorfd == -1)
		return (-1);
	push_name_and_cmnt_to_file(data, buf1, buf2);
	while (file_lst)
	{
		if (file_lst->empty == 0)
		{
			write(data->dotcorfd, &file_lst->opcodevalue, 1);
			if (file_lst->octalvalue)
				write(data->dotcorfd, &file_lst->octalvalue, 1);
			push_list_to_file(file_lst, data, 0, 0);
		}
		file_lst = file_lst->next;
	}
	return (1);
}
