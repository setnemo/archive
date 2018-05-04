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
#define SUMARRM(x, y) (x -= (y[0] + y[1] + y[2] + y[3]))
#define GL get_labelvaluesize

int			setfixsize(t_asmlst *file_lst, int j);

void		goup(t_asmlst *file_lst, char *str, int flag, int j)
{
	int			allb;
	t_asmlst	*lst;

	allb = 0;
	while (file_lst && --flag)
	{
		file_lst = file_lst->next;
	}
	if (file_lst->islabel[j] && ft_strequ(file_lst->islabel[j], str))
		ft_printf("!!!!!!!!goup!!!!!!!!!\n");
	lst = file_lst;
	while (file_lst)
	{
		if (file_lst->label && ft_strequ(str, file_lst->label))
				break ;
		SUMARR(allb, file_lst->listsize);
		ft_printf("=||goup|file_lst->label|%s||=>allb:%#.4x\n", file_lst->label, allb);
		file_lst = file_lst->next;
	}
	lst->value_arg[j] = allb;
	ft_printf("=||allb:%#.4x||goup|str[%s]||=>allb:%#.4x\n", allb, str, lst->value_arg[j]);

	// ft_printf("=||goup||%s||=>allb:%#.4x\n", str, allb);

}

void		goback(t_asmlst *file_lst, char *str, int flag, int j)
{
	if (str)
		;
	int allb;
	int fix;
	t_asmlst *lst = NULL;
	allb = 0;
	lst = file_lst;
	file_lst = file_lst->next;
	ft_printf("=================%i================\n", flag);
	lst = file_lst;
		ft_printf("\t\t\t\tNUMBER:%d\n", lst->number);
	ft_printf("\t\t\t\t-----------|||||||--------------------------------------------------||||-----------\n");
	ft_printf("\t\t\t\tNUMBER:%d\n", file_lst->number);

	ft_printf("\t\t\t\tlabel_name:%s\n", file_lst->label);
	ft_printf("\t\t\t\topcode:%s\n", file_lst->op_code);
	ft_printf("\t\t\t\tcount arg:%d\n", file_lst->count_arg);
	ft_printf("\t\t\t\tlabel link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
	ft_printf("\t\t\t\tbyte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
	ft_printf("\t\t\t\tvalue arg:%#x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
	ft_printf("\t\t\t\topcodevalue:%#.2x\n", file_lst->opcodevalue);
	ft_printf("\t\t\t\toctalvalue:%#.2x\n", file_lst->octalvalue);
	ft_printf("\t\t\t\tlabelsize:%d\n", file_lst->labelsize);
	ft_printf("\t\t\t\tlistsize:%d.%d.%d.%d\n", file_lst->listsize[0], file_lst->listsize[1], file_lst->listsize[2], file_lst->listsize[3]);
	ft_printf("\t\t\t\t-----------|||||||--------------------------------------------------||||-----------\n");
	while (file_lst && flag--)
	{
		// ft_printf("lst->value_arg[%s], file_lst->bytecode[%i], file_lst->labelsize = [%i];\n", file_lst->islabel[j], file_lst->bytecode[j], file_lst->labelsize);
		// ft_printf("=3=>allb:%i\n", allb);
		ft_printf("how operation? %i\n", flag);
		SUMARR(allb, file_lst->listsize);
		if (file_lst->next)
			file_lst = file_lst->next;
		else
			break ;
	}
	fix = setfixsize(file_lst, j);
	fix -= --allb;
	file_lst->value_arg[j] = fix;
	ft_printf("\t\t\t\t-----------|||||||--------------------.............--------------------||||-----------\n");
	ft_printf("\t\t\t\tNUMBER:%d\n", file_lst->number);

	ft_printf("\t\t\t\tlabel_name:%s\n", file_lst->label);
	ft_printf("\t\t\t\topcode:%s\n", file_lst->op_code);
	ft_printf("\t\t\t\tcount arg:%d\n", file_lst->count_arg);
	ft_printf("\t\t\t\tlabel link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
	ft_printf("\t\t\t\tbyte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
	ft_printf("\t\t\t\tvalue arg:%#x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
	ft_printf("\t\t\t\topcodevalue:%#.2x\n", file_lst->opcodevalue);
	ft_printf("\t\t\t\toctalvalue:%#.2x\n", file_lst->octalvalue);
	ft_printf("\t\t\t\tlabelsize:%d\n", file_lst->labelsize);
	ft_printf("\t\t\t\tlistsize:%d.%d.%d.%d\n", file_lst->listsize[0], file_lst->listsize[1], file_lst->listsize[2], file_lst->listsize[3]);
	ft_printf("\t\t\t\t-----------|||||||--------------------.............--------------------||||-----------\n");
	// ft_printf("=||allb:%#.4x||fix:%#.4x|goback|str[%s]||=>allb:%#.4x\n", allb, fix, str, file_lst->value_arg[j]);

}

void		get_labelvaluesize(t_asmlst *file_lst, char *str, int countl, int j)
{
	int all;
	int flag;
	int tempstart;
	t_asmlst *lst;
	t_asmlst *lst2;

	lst = file_lst;
	all = 0;
	flag = 0;
	lst2 = NULL;
	tempstart = countl;
	
	while (file_lst && tempstart--)
	{
		flag++;
		if (file_lst->label && ft_strequ(str, file_lst->label))
		{
			lst2 = file_lst;
			all = flag;
		}
		file_lst = file_lst->next;
	}
	// ft_printf("\t\t\t-----------|||||||%i|||_%i_|||%i|||||||-----------\n", flag, all, countl);
	if (!all)
	{
		ft_printf("\t\t\tcount UP %i\n", countl);
		goup(lst, str, countl, j);
	}
	else
	{
		ft_printf("\t\t\tcount BACK %i\n", countl - all);
		goback(lst2->prev, str, countl - all, j);
	}
}

void		get_file_lst(t_asm *data, int i, int countlst)
{
	t_asmlst	*file_lst = NULL;

	file_lst = data->next;

	while (file_lst)
	{
		file_lst->octal = get_octal(file_lst->op_code);
		file_lst->labelsize = get_labelsize(file_lst->op_code);
		file_lst->opcodevalue = get_opcodevalue(file_lst->op_code);
		if (file_lst->octal)
			file_lst->octalvalue = get_octalvalue(file_lst->bytecode);
		get_listsize(file_lst);
		SUMARR(data->allbytes, file_lst->listsize);
		file_lst = file_lst->next;
	}
	file_lst = data->next;
	while (file_lst && ++countlst)
	{
		i = 0;
		while (i < 3)
		{
			// ft_printf("\t\tnow check:%s\n", file_lst->islabel[i]);
			if (file_lst->islabel[i])
			{
				ft_printf("\t\t\t\t======>NUMBER:%d (%i)\n", file_lst->number, i);
				GL(data->next, file_lst->islabel[i], countlst, i);
			}
			i++;
		}
		ft_printf("\t-----------||||||||||===%i==|||||||||-----------\n", countlst);
		ft_printf("\tNUMBER:%d\n", file_lst->number);
		ft_printf("\tlabel_name:%s\n", file_lst->label);
		ft_printf("\topcode:%s\n", file_lst->op_code);
		ft_printf("\tcount arg:%d\n", file_lst->count_arg);
		ft_printf("\tlabel link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
		ft_printf("\tbyte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
		ft_printf("\tvalue arg:%#x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
		ft_printf("\topcodevalue:%#.2x\n", file_lst->opcodevalue);
		ft_printf("\toctalvalue:%#.2x\n", file_lst->octalvalue);
		ft_printf("\tlabelsize:%d\n", file_lst->labelsize);
		ft_printf("\tlistsize:%d.%d.%d.%d\n", file_lst->listsize[0], file_lst->listsize[1], file_lst->listsize[2], file_lst->listsize[3]);

		ft_printf("\t-----------||||||||||=========|||||||||-----------\n");
		file_lst = file_lst->next;
	}
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
	int num = 0;
	while (file_lst)
	{
		num++;
		file_lst->number = num;
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
	get_file_lst(data, 0, 0);

	//g_optab[0].name;


	file_lst = data->next;
	while (file_lst)
	{
		
		ft_printf("------==============================----\n");
		ft_printf("NUMBER:%d\n", file_lst->number);
		ft_printf("label_name:%s\n", file_lst->label);
		ft_printf("opcode:%s\n", file_lst->op_code);
		ft_printf("count arg:%d\n", file_lst->count_arg);
		ft_printf("label link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
		ft_printf("byte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
		ft_printf("value arg:%#x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
		ft_printf("opcodevalue:%#.2x\n", file_lst->opcodevalue);
		ft_printf("octalvalue:%#.2x\n", file_lst->octalvalue);
		ft_printf("labelsize:%d\n", file_lst->labelsize);
		ft_printf("\tlistsize:%d.%d.%d.%d\n", file_lst->listsize[0], file_lst->listsize[1], file_lst->listsize[2], file_lst->listsize[3]);

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
		ft_printf("now saving byte::1:===%#.4x\n", file_lst->opcodevalue);
		write(data->dotcorfd, &file_lst->opcodevalue, 1);
		if (file_lst->octalvalue)
		{
			write(data->dotcorfd, &file_lst->octalvalue, 1);
			ft_printf("now saving byte::1:===%#.4x\n", file_lst->octalvalue);
		}
		i = 0;
		ft_printf("value arg:%#x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
				ft_printf("\tNUMBER:%d\n", file_lst->number);
		while (i < 3)
		{
			if (file_lst->bytecode[i])
			{
				t_byterange.num = 0;
				t_byterange.num = file_lst->value_arg[i];
				ft_printf("t_byterange.num:%i\n", t_byterange.num);
				temp1 = getwriteargsize(file_lst, i);
				ft_printf("now saving byte::%i:===%#.4x\n", temp1, file_lst->value_arg[i]);
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
					// write(data->dotcorfd, &file_lst->value_arg[i], 2);
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


int			setfixsize(t_asmlst *file_lst, int j)
{
	int ret;

	if (file_lst->bytecode[j] == 1)
	{
		ft_printf("ret = 0xFF;return (ret);\n");
		ret = 0xFF;
		return (ret);
	}
	if (file_lst->bytecode[j] == 3)
	{
		ft_printf("ret = 0xFFFF;return (ret);\n");
		ret = 0xFFFF;
		return (ret);
	}

	if (file_lst->labelsize == 2)
	{
		ft_printf("ret = 0xFFFF;return (ret);\n");
		ret = 0xFFFF;
		return (ret);
	}
	ft_printf("ret = 0xFFFFFFFF;return (ret);\n");
	ret = 0xFFFFFFFF;
	return (ret);
}

