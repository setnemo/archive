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

void		goup(t_asmlst *file_lst, char *str, int flag, int j)
{
	int			allb;
	t_asmlst	*lst;
	allb = 0;
	// file_lst = file_lst->next;
	// if (str)
	// 	;
	// ft_printf("flag:%i\n", flag);
	while (file_lst && flag--)
	{
		// lst = file_lst;
		lst = file_lst;
		if (ft_strequ(file_lst->islabel[j], str))
			break ;
		file_lst = file_lst->next;
	}
	// lst = file_lst;
	if (!j)
		allb = file_lst->listsize[2] + file_lst->listsize[3];
	else if (j == 1)
		allb = file_lst->listsize[3];
	ft_printf("\t\t\t\top_code|||||||||%s\n", file_lst->op_code);
	ft_printf("\t\t\t\tallb||||||||||||%#.2x::\n", allb);
	file_lst = file_lst->next;
	while (file_lst)
	{
		allb += file_lst->listsize[0];
		allb += file_lst->listsize[1];
		allb += file_lst->listsize[2];
		allb += file_lst->listsize[3];
		ft_printf("\t\t\t\top_code|||||||||%s\n", file_lst->op_code);
		ft_printf("\t\t\t\tlabel|||||||||||%s\n", file_lst->label);
		ft_printf("\t\t\t\tallb||||||||||||%#.2x::\n", allb);
		if (file_lst->label && ft_strequ(str, file_lst->label))
				break ;
		file_lst = file_lst->next;
	}
	ft_printf("||||UP||||::%#.2x::\n", allb);
	lst->value_arg[j] =  allb;
	ft_printf("||||UP||||||::%#.2x::\n", lst->value_arg[j]);
}

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
		allb += file_lst->listsize[1];
		allb += file_lst->listsize[2];
		allb += file_lst->listsize[3];
		file_lst = file_lst->next;
	}
	ft_printf("||||||||||||::%#.2x::\n", allb);
	int test = 0xFFFF;
	file_lst->value_arg[j] =  test - allb;
	ft_printf("||||||||||||::%#.2x::\n", file_lst->value_arg[j]);
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
	if (j)
		;
	tempstart = countl;
	ft_printf("HERAK %s |%i-%i|\n", str, countl, j);
	while (file_lst && countl - 1)
	{
		ft_printf("HERAK go back %s |%i-%i|\n", str, countl, j);
		if (ft_strequ(str, file_lst->label))
		{
			flag = countl;
			break ;
		}
		countl--;
		file_lst = file_lst->next;
	}
	if (!flag)
	// {
	// 	;//если лейбл раньше, чем написан в коде. У нас есть флаг, в котором количество листов до указателя на лейбл
	// 	// если tempstart != countl тогда у нас надо идти в обратную сторону
	// }
	// else
	{
		while (file_lst)
		{
			ft_printf("HERAK go up %s |%i-%i|\n", str, countl, j);
			flag++;//у нас будет флаг на количество листов, на которые надо пройти вперед.
			if (ft_strequ(str, file_lst->label))
				break ;
			file_lst = file_lst->next;
		}
	}
	else
	{
		goback(file_lst, str, tempstart - flag, j); // тогда флаг это номер листа для похода в обратную сторону - flag - how incr lst 
		return ;
	}
	goup(lst, str, flag, j);
		// gofoward(file_lst, str, flag, j); // флаг у нас это количество листов, которые надо пройти вперед
}

int			to_file(t_list **fl_lst, t_asm *data)
{
	t_fls		*fls;
	t_asmlst	*file_lst = NULL;

	fls = (*fl_lst)->content;
	ft_printf("name:%s\n", fls->name);
	ft_printf("comment:%s\n", fls->cmnt);
	data->filename = ft_strdup(fls->name);
	data->filecomment = ft_strdup(fls->cmnt);
	file_lst = (t_asmlst*)malloc(sizeof(t_asmlst));
	data->next = file_lst;
	ft_bzero(file_lst, sizeof(t_asmlst));
	file_lst = data->next;
	read_tree(file_lst,NULL, fls->spltd);
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
		ft_printf("value arg:%#.2x.%#.2x.%#.2x\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
		file_lst = file_lst->next;
	}


	int		magic;
	char	buf1[PROG_NAME_LENGTH - ft_strlen(data->filename)];
	char	buf2[COMMENT_LENGTH - ft_strlen(data->filecomment)];
	int		fix;

	data->dotcorfd = open(data->dotcorname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
