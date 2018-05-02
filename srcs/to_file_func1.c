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
#define LS2 2
#define LS4 4

void		goback(t_asmlst *file_lst, char *str, int flag, int j)
{
	int allb;

	allb = 0;
	file_lst = file_lst->next;
	if (str)
		;
	ft_printf("flag:%i\n", flag);
	while (file_lst && flag--)
	{
		// flag--;
		//allb += file_lst->listsize[0];
		allb += file_lst->listsize[1];
		allb += file_lst->listsize[2];
		allb += file_lst->listsize[3];
		// if (ft_strequ(str, file_lst->islabel[j]))
		// {
		// 	file_lst = file_lst->next;
		// 	break ;
		// }
		// else
			file_lst = file_lst->next;
	}
	ft_printf("::%#.2x::\n", allb);
	int test = 0xFFFF;
	file_lst->value_arg[j] =  test - allb;
}

void		get_labelvaluesize(t_asmlst *file_lst, char *str, int countl, int j)
{
	int all;
	int flag;
	int tempstart;

	all = 0;
	flag = 0;
	if (j)
		;
	tempstart = countl;
	while (file_lst && countl)
	{
		if (ft_strequ(str, file_lst->label))
		{
			flag = countl;
			break ;
		}
		countl--;
		file_lst = file_lst->next;
	}
	if (flag)
	{
		;//если лейбл раньше, чем написан в коде. У нас есть флаг, в котором количество листов до указателя на лейбл
		// если tempstart != countl тогда у нас надо идти в обратную сторону
	}
	else
	{
		while (file_lst)
		{
			flag++;//у нас будет флаг на количество листов, на которые надо пройти вперед.
			if (ft_strequ(str, file_lst->label))
				break ;
			file_lst = file_lst->next;
		}
	}
	if (tempstart != countl)
		goback(file_lst, str, tempstart - flag, j); // тогда флаг это номер листа для похода в обратную сторону - flag - how incr lst 
	else
		;
		// gofoward(file_lst, str, flag, j); // флаг у нас это количество листов, которые надо пройти вперед
}

void		get_listsize(t_asmlst *file_lst)
{
	int i;

	i = 1;
	if (file_lst->octal)
		file_lst->listsize[0] = 2;
	else
		file_lst->listsize[0] = 1;
	while (i < 4)
	{
		if (file_lst->bytecode[i - 1])
		{
			if (file_lst->bytecode[i - 1] == 1)
				file_lst->listsize[i] = 1;
			if (file_lst->bytecode[i - 1] == 2)
				file_lst->listsize[i] = file_lst->labelsize;
			if (file_lst->bytecode[i - 1] == 3)
				file_lst->listsize[i] = 2;
		}
		i++;
	}
}

int			get_octalvalue(char val[])
{
	int		i;
	short	value;
	int		bit;

	i = 0;
	value = 0;
	bit = 7;
	while (i < 3)
	{
		if (val[i] == 3)
		{
			value |= 1 << bit;
			value |= 1 << (bit - 1);
		}
		if (val[i] == 2)
			value |= 1 << bit;
		if (val[i] == 1)
			value |= 1 << (bit - 1);
		bit -= 2;
		i++;
	}
	return (value);
}

int			get_opcodevalue(char *opcode)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_optab[i].name, opcode))
			break ;
		i++;
	}
	return (g_optab[i].op_code);
}

int			get_labelsize(char *opcode)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_optab[i].name, opcode))
			break ;
		i++;
	}
	if (g_optab[i].op_code > 8 && g_optab[i].op_code != 13 && g_optab[i].op_code != 16)
		return (LS2);
	return (LS4);
}

int			get_octal(char *opcode)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(g_optab[i].name, opcode))
			break ;
		i++;
	}
	return (g_optab[i].codage);
}

void		read_tree(t_asmlst *file_lst, t_fls *fls, t_spl *spl)
{
	t_list		*tmp;
	int			i;

	tmp = fls->spltd;
	while (tmp)
	{
		spl = (t_spl*)tmp->content;
		if (spl->lbl)
			file_lst->label = ft_strdup(spl->lbl);
		if (!spl->op_code && tmp->next)
		{
			spl = (t_spl*)tmp->next->content;
			tmp = tmp->next;
		}
		if (spl->op_code)
			file_lst->op_code = ft_strdup(spl->op_code);
		file_lst->count_arg = spl->q_arg;
		i = 0;
		while (i < 3)
		{
			if (spl->islbl[i])
				file_lst->islabel[i] = ft_strdup(spl->islbl[i]);
			i++;
		}
		i = 0;
		while (i < 3)
		{
			file_lst->bytecode[i] = spl->bc[i];
			i++;
		}
		i = 0;
		while (i < 3)
		{
			file_lst->value_arg[i] = spl->value[i];
			i++;
		}
		if (tmp->next != NULL)
		{
			spl = (t_spl*)tmp->next->content;
			tmp = tmp->next;
			file_lst->next = (t_asmlst*)malloc(sizeof(t_asmlst));
			file_lst = file_lst->next;
			ft_bzero(file_lst, sizeof(t_asmlst));
		}
		else
			break ;
	}
}

int			to_file(t_list **fl_lst, t_asm *data)
{
	t_fls		*fls;
	t_asmlst	*file_lst = NULL;
	int			i;

	fls = (*fl_lst)->content;
	ft_printf("name:%s\n", fls->name);
	ft_printf("comment:%s\n", fls->cmnt);
	data->filename = ft_strdup(fls->name);
	data->filecomment = ft_strdup(fls->cmnt);
	file_lst = (t_asmlst*)malloc(sizeof(t_asmlst));
	data->next = file_lst;
	ft_bzero(file_lst, sizeof(t_asmlst));
	file_lst = data->next;
	read_tree(file_lst, fls, NULL);
	data->dotcorfd = open(data->dotcorname, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	while (file_lst)
	{
		ft_printf("-----------start-----------\n");
		ft_printf("label_name:%s\n", file_lst->label);
		ft_printf("opcode:%s\n", file_lst->op_code);
		ft_printf("count arg:%d\n", file_lst->count_arg);
		ft_printf("label link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
		ft_printf("byte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
		ft_printf("value arg:%d.%d.%d\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
		file_lst->octal = get_octal(file_lst->op_code);
		ft_printf("octal:%d\n", file_lst->octal);
		file_lst->labelsize = get_labelsize(file_lst->op_code);
		ft_printf("labelsize:%d\n", file_lst->labelsize);
		file_lst->opcodevalue = get_opcodevalue(file_lst->op_code);
		ft_printf("opcodevalue:%#.2x\n", file_lst->opcodevalue);
		if (file_lst->octal)
			file_lst->octalvalue = get_octalvalue(file_lst->bytecode);
		ft_printf("octalvalue:%#.2x\n", file_lst->octalvalue);
		get_listsize(file_lst);
		ft_printf("listsize:%d.%d.%d.%d\n", file_lst->listsize[0], file_lst->listsize[1], file_lst->listsize[2], file_lst->listsize[3]);
		data->allbytes += file_lst->listsize[0];
		data->allbytes += file_lst->listsize[1];
		data->allbytes += file_lst->listsize[2];
		data->allbytes += file_lst->listsize[3];
		file_lst = file_lst->next;
	}
	ft_printf("alllll:%#.2x\n", data->allbytes);
	//g_optab[0].name;

	int countlst;

	countlst = 0;
	file_lst = data->next;
	while (file_lst)
	{
		i = 0;
		countlst++;
		while (file_lst->islabel[i])
		{
			if (file_lst->islabel[i])
				get_labelvaluesize(data->next, file_lst->islabel[i], countlst, i);
			i++;
		}
		file_lst = file_lst->next;
	}
	file_lst = data->next;
	while (file_lst)
	{
		ft_printf("-----------start2-----------\n");
		ft_printf("label_name:%s\n", file_lst->label);
		ft_printf("opcode:%s\n", file_lst->op_code);
		ft_printf("count arg:%d\n", file_lst->count_arg);
		ft_printf("label link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
		ft_printf("byte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
		ft_printf("value arg:%#.2x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
		file_lst = file_lst->next;
	}


	int		magic;
	char	buf1[PROG_NAME_LENGTH - ft_strlen(data->filename)];
	char	buf2[COMMENT_LENGTH - ft_strlen(data->filecomment)];
	int		fix;

	fix = 0;
	if ((PROG_NAME_LENGTH + 1) % 4 != 0)
		fix += 4 - (PROG_NAME_LENGTH + 1) % 4;
	// ft_printf("fix after:%i\n", fix);
	if ((COMMENT_LENGTH + 1) % 4 != 0)
		fix += 4 - (COMMENT_LENGTH + 1) % 4;
	// ft_printf("fix after:%i\n", fix);

	magic = COREWAR_EXEC_MAGIC;
	magic = ((magic >> 24) & 0xff) | ((magic << 8) & 0xff0000) |
		((magic >> 8) & 0xff00) | ((magic << 24) & 0xff000000);
	data->allbytes = ((data->allbytes >> 24) & 0xff) | ((data->allbytes << 8) & 0xff0000) |
		((data->allbytes >> 8) & 0xff00) | ((data->allbytes << 24) & 0xff000000);
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

	return (0);
}
