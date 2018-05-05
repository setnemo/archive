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

int			push_data_to_file(t_asm *data)
{
	int			magic;
	char		buf1[PROG_NAME_LENGTH - ft_strlen(data->filename)];
	char		buf2[COMMENT_LENGTH - ft_strlen(data->filecomment)];
	int			fix;
	t_asmlst	*file_lst = NULL;
	int			i;

	file_lst = data->next;
	data->dotcorfd = open(data->dotcorname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fix = 0;
	if ((PROG_NAME_LENGTH + 1) % 4 != 0)
		fix += 4 - (PROG_NAME_LENGTH + 1) % 4;
	if ((COMMENT_LENGTH + 1) % 4 != 0)
		fix += 4 - (COMMENT_LENGTH + 1) % 4;

	magic = COREWAR_EXEC_MAGIC;
	int x;
	x = magic;
	x = O1 | O2;
	magic = x;
	x = data->allbytes;
	x = O1 | O2;
	data->allbytes = x;
	write(data->dotcorfd, &magic, 4);
	ft_bzero(buf1, PROG_NAME_LENGTH  - ft_strlen(data->filename));
	ft_bzero(buf2, COMMENT_LENGTH - ft_strlen(data->filecomment)); 
	write(data->dotcorfd, data->filename, ft_strlen(data->filename));
	write(data->dotcorfd, buf1, PROG_NAME_LENGTH - ft_strlen(data->filename));
	write(data->dotcorfd, buf1, 4);
	write(data->dotcorfd, &data->allbytes, 4);
	write(data->dotcorfd, data->filecomment, ft_strlen(data->filecomment));
	write(data->dotcorfd, buf2, COMMENT_LENGTH - ft_strlen(data->filecomment));
	write(data->dotcorfd, buf1, 4);
	int temp1;
	int k;
	while (file_lst)
	{
		if (file_lst->empty == 0)
		{
			write(data->dotcorfd, &file_lst->opcodevalue, 1);
			if (file_lst->octalvalue)
				write(data->dotcorfd, &file_lst->octalvalue, 1);
			i = 0;
			while (i < 3)
			{
				if (file_lst->bytecode[i])
				{
					t_byterange.num = 0;
					t_byterange.num = file_lst->value_arg[i];
					temp1 = getwriteargsize(file_lst, i);
					if (temp1 == 4)
					{
						k = 3;
						while (42)
						{
							write(data->dotcorfd, &t_byterange.ch[k], 1);
							k--;
							if (k == -1)
								break ;
						}
					}
					if (temp1 == 2)
					{
						write(data->dotcorfd, &t_byterange.ch2[1], 1);
						write(data->dotcorfd, &t_byterange.ch2[0], 1);
					}
					if (temp1 == 1)
						write(data->dotcorfd, &file_lst->value_arg[i], 1);
				}
				i++;
			}
		}
		file_lst = file_lst->next;
	}
	return (0);
}