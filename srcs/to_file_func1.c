/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_file_func1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/04/28 11:49:33 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "error_asm.h"
#include "op.h"
#define SUMARR(x, y) (x += (y[0] + y[1] + y[2] + y[3]))

void		goup(t_asmlst *file_lst, char *str, int flag, int j)
{
	int			allb;
	t_asmlst	*lst;

	allb = 0;
	while (file_lst && flag--)
	{
		lst = file_lst;
		if (ft_strequ(file_lst->islabel[j], str))
			break ;
		file_lst = file_lst->next;
	}
	if (!j)
		allb = file_lst->listsize[2] + file_lst->listsize[3];
	else if (j == 1)
		allb = file_lst->listsize[3];
	file_lst = file_lst->next;
	while (file_lst)
	{
		SUMARR(allb, file_lst->listsize);
		if (file_lst->label && ft_strequ(str, file_lst->label))
				break ;
		file_lst = file_lst->next;
	}
	lst->value_arg[j] = allb;
}

int			setfixsize(t_asmlst *file_lst, int j)
{
	int ret;

	if (file_lst->bytecode[j] == 1)
	{
		ret = 0xFF;
		return (ret);
	}
	if (file_lst->bytecode[j] == 3)
	{
		ret = 0xFFFF;
		return (ret);
	}
	if (file_lst->labelsize == 2)
	{
		ret = 0xFFFF;
		return (ret);
	}
	ret = 0xFFFFFFFF;
	return (ret);
}

void		goback(t_asmlst *file_lst, char *str, int flag, int j)
{
	int allb;
	int fix;
	t_asmlst *lst = NULL;
	allb = 0;
	// ft_printf("===>flag:%i\n", flag);
	while (file_lst)
	{
		// ft_printf("===>allb:%i\n", allb);
		if (file_lst->islabel[j] && ft_strequ(str, file_lst->islabel[j]))
				break ;
		file_lst = file_lst->next;
	}
	fix = setfixsize(file_lst, j);
	lst = file_lst;
	while (file_lst && flag--)
	{
		// ft_printf("===>allb:%i\n", allb);
		SUMARR(allb, file_lst->listsize);
		file_lst = file_lst->prev;
	}
	// ft_printf("=||||=>allb:%i\n", allb);
	lst->value_arg[j] = fix - allb - 1;
}

void		get_labelvaluesize(t_asmlst *file_lst, char *str, int countl, int j)
{
	int all;
	int flag;
	int tempstart;

	t_asmlst *lst;
	lst = file_lst;
	all = 0;
	flag = 0;
	tempstart = countl;
	while (file_lst && --tempstart)
	{
		flag = tempstart;
		ft_printf("=||get_labelvaluesize||=>file_lst->label:%s and str:%s\n", file_lst->label, str);
		if (file_lst->label && ft_strequ(str, file_lst->label))
		{
			flag = 0;
			break ;
		}
		file_lst = file_lst->next;
	}
	if (!flag)
	{
		flag = 0;
		while (file_lst)
		{
			flag++;
			if (file_lst->label && ft_strequ(str, file_lst->label))
				break ;
			file_lst = file_lst->next;
		}
	}
	else
	{
		ft_printf("\t\t\tсчитать назад\n");
		goback(file_lst, str, countl - flag, j);
		return ;
	}
	ft_printf("\t\t\tсчитать вперед\n");
	goup(lst, str, flag, j);
}

void		push_data_to_file(t_asm *data);

int			to_file(t_list **fl_lst, t_asm *data)
{
	t_fls		*fls;
	t_asmlst	*file_lst = NULL;
	t_asmlst	*back = NULL;

	fls = (*fl_lst)->content;
	// ft_printf("name:%s\n", fls->name);
	// ft_printf("comment:%s\n", fls->cmnt);
	data->filename = ft_strdup(fls->name);
	data->filecomment = ft_strdup(fls->cmnt);
	file_lst = (t_asmlst*)malloc(sizeof(t_asmlst));
	data->next = file_lst;
	ft_bzero(file_lst, sizeof(t_asmlst));
	file_lst = data->next;
	read_tree(file_lst,NULL, fls->spltd);
	while (file_lst)
	{
		if (file_lst->next)
		{
			back = file_lst;
			file_lst = file_lst->next;
			file_lst->prev = back;
		}
		else
	
			break ;
	}

	file_lst = data->next;
	get_file_lst(file_lst, data, 0, 0);

	//g_optab[0].name;


	file_lst = data->next;
	while (file_lst)
	{
		
		ft_printf("-----------start2-----------\n");
		ft_printf("label_name:%s\n", file_lst->label);
		ft_printf("opcode:%s\n", file_lst->op_code);
		ft_printf("count arg:%d\n", file_lst->count_arg);
		ft_printf("label link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
		ft_printf("byte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
		ft_printf("value arg:%#x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
		ft_printf("opcodevalue:%#.2x\n", file_lst->opcodevalue);
		ft_printf("octalvalue:%#.2x\n", file_lst->octalvalue);
		ft_printf("labelsize:%d\n", file_lst->labelsize);
		file_lst = file_lst->next;
	}
		// ft_printf("-----------BACK-----------\n");

	// while (file_lst)
	// {
		// ft_printf("-----------start2-----------\n");
		// ft_printf("label_name:%s\n", file_lst->label);
		// ft_printf("opcode:%s\n", file_lst->op_code);
		// ft_printf("count arg:%d\n", file_lst->count_arg);
		// ft_printf("label link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
		// ft_printf("byte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
		// ft_printf("value arg:%#x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
		// ft_printf("opcodevalue:%#.2x\n", file_lst->opcodevalue);
		// ft_printf("octalvalue:%#.2x\n", file_lst->octalvalue);
		// ft_printf("labelsize:%d\n", file_lst->labelsize);
	// 	file_lst = file_lst->prev;
	// }

	push_data_to_file(data);
	return (0);
}
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

#define PUSHBYTES(x) (x = ((x >> 24) & 0xff) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | ((x << 24) & 0xff000000))

unsigned char	swap_bits(unsigned char octet)
{
	return (octet >> 4 | octet << 4);
}

void		push_data_to_file(t_asm *data)
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
	// ft_printf("fix after:%i\n", fix);
	if ((COMMENT_LENGTH + 1) % 4 != 0)
		fix += 4 - (COMMENT_LENGTH + 1) % 4;
	// ft_printf("fix after:%i\n", fix);

	magic = COREWAR_EXEC_MAGIC;
	PUSHBYTES(magic);
	PUSHBYTES(data->allbytes);
	// data->allbytes = ((data->allbytes >> 24) & 0xff) | ((data->allbytes << 8) & 0xff0000) |
	// 	((data->allbytes >> 8) & 0xff00) | ((data->allbytes << 24) & 0xff000000);
	write(data->dotcorfd, &magic, 4); // MAGIC PRINT
	ft_bzero(buf1, PROG_NAME_LENGTH  - ft_strlen(data->filename));
	ft_bzero(buf2, COMMENT_LENGTH - ft_strlen(data->filecomment)); 
	write(data->dotcorfd, data->filename, ft_strlen(data->filename)); //NAME PRINT
	write(data->dotcorfd, buf1, PROG_NAME_LENGTH - ft_strlen(data->filename));// NAME SPACE PRINT
	write(data->dotcorfd, buf1, 4); //NULL PRINT
	write(data->dotcorfd, &data->allbytes, 4); // SIZE BYTECODE PRINT
	write(data->dotcorfd, data->filecomment, ft_strlen(data->filecomment)); //COMMENT PRINT
	write(data->dotcorfd, buf2, COMMENT_LENGTH - ft_strlen(data->filecomment)); // COMMENT SPACE PRINT
	write(data->dotcorfd, buf1, 4); // NULL
	int temp1;
	int k;
	while (file_lst)
	{
		// ft_printf("now saving byte::1:===%#.4x\n", file_lst->opcodevalue);
		write(data->dotcorfd, &file_lst->opcodevalue, 1);
		if (file_lst->octalvalue)
		{
			write(data->dotcorfd, &file_lst->octalvalue, 1);
			// ft_printf("now saving byte::1:===%#.4x\n", file_lst->octalvalue);
		}
		i = 0;
		while (i < 3)
		{
			if (file_lst->bytecode[i])
			{
				t_byterange.num = file_lst->value_arg[i];
				temp1 = getwriteargsize(file_lst, i);
				// ft_printf("now saving byte::%i:===%#.4x\n", temp1, file_lst->value_arg[i]);
				if (temp1 == 4)
				{
					k = 3;
					while (42)
					{
						write(data->dotcorfd, &t_byterange.ch[k], 1);
						// ft_printf("k==%i, :%.2x:\n", k, t_byterange.ch[k]);
						k--;
						if (k == -1)
							break ;
					}
					// file_lst->value_arg[i] = swap_bits(file_lst->value_arg[i]);
				}
				if (temp1 == 2)
				{
					// file_lst->value_arg[i] = swap_bits(file_lst->value_arg[i]);
					// ft_printf(":%.2x:\n", t_byterange.ch[1]);
					// ft_printf(":%.2x:\n", t_byterange.ch[0]);
					write(data->dotcorfd, &t_byterange.ch2[1], 1);
					write(data->dotcorfd, &t_byterange.ch2[0], 1);
				}
				if (temp1 == 1)
					write(data->dotcorfd, &file_lst->value_arg[i], 1);
			}
			i++;
		}
		file_lst = file_lst->next;
	}






}
