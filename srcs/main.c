/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

int			to_file(t_list **fl_lst, t_asm *data)
{
	t_fls		*fls;
	t_spl		*spl;
	t_asmlst	*file_lst = NULL;
	t_list		*tmp;
	int			i;

	fls = (*fl_lst)->content;
	ft_printf("name:%s\n", fls->name);
	ft_printf("comment:%s\n", fls->cmnt);
	data->filename = ft_strdup(fls->name);
	data->filecomment = ft_strdup(fls->cmnt);
	tmp = fls->spltd;
	file_lst = (t_asmlst*)malloc(sizeof(t_asmlst));
	data->next = file_lst;
	ft_bzero(file_lst, sizeof(t_asmlst));
	while (tmp)
	{
		spl = (t_spl*)tmp->content;
		ft_printf("-----------start-----------\n");
		ft_printf("label_name:%s\n", spl->lbl);
		if (spl->lbl)
			file_lst->label = ft_strdup(spl->lbl);
		if (!spl->op_code && tmp->next)
		{
			spl = (t_spl*)tmp->next->content;
			tmp = tmp->next;
		}
		ft_printf("opcode:%s\n", spl->op_code);
		if (spl->op_code)
			file_lst->op_code = ft_strdup(spl->op_code);
		ft_printf("count arg:%d\n", spl->q_arg);
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
		ft_printf("label link:%s.%s.%s\n", spl->islbl[0], spl->islbl[1], spl->islbl[2]);
		ft_printf("byte code:%d.%d.%d\n", spl->bc[0], spl->bc[1], spl->bc[2]);
		ft_printf("value arg:%d.%d.%d\n", spl->value[0], spl->value[1], spl->value[2]);
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
	file_lst = data->next;
	ft_printf("-----------||||-----------\n");
	while (file_lst)
	{
		ft_printf("-----------start-----------\n");
		ft_printf("label_name:%s\n", file_lst->label);
		ft_printf("opcode:%s\n", file_lst->op_code);
		ft_printf("count arg:%d\n", file_lst->count_arg);
		ft_printf("label link:%s.%s.%s\n", file_lst->islabel[0], file_lst->islabel[1], file_lst->islabel[2]);
		ft_printf("byte code:%d.%d.%d\n", file_lst->bytecode[0], file_lst->bytecode[1], file_lst->bytecode[2]);
		ft_printf("value arg:%d.%d.%d\n", file_lst->value_arg[0], file_lst->value_arg[1], file_lst->value_arg[2]);
		file_lst = file_lst->next;
	}
	ft_printf("\n\n\n\nG:%s\n", g_optab[0].name);
	return (0);
}

void		cleaning_asm_lst_lst_spltd(t_spl *lst)
{
	t_list	*ptr;
	t_list	*ptr2;
	int		i;

	i = 0;
	if (lst->lbl)
		ft_strdel(&lst->lbl);
	if (lst->op_code != NULL)
		ft_strdel(&(lst->op_code));
	while(i < 3)
	{
		if (lst->islbl[i])
			ft_strdel(&(lst->islbl[i]));
		i++;
	}
	ptr = lst->args;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		if (ptr2->content)
			free(ptr2->content);
		free(ptr2);
	}
}

void		cleaning_asm_lst_spltd(t_list *lst)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		if (ptr2->content)
		{
			cleaning_asm_lst_lst_spltd(ptr2->content);
			free(ptr2->content);
		}
		free(ptr2);
	}
}
void		cleaning_asm_lst_instr(t_list *lst)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(ptr2->content);
		free(ptr2);
	}
}

void		cleaning_asm_lst_lines(t_list *lst)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(ptr2->content);
		free(ptr2);
	}
}

void		cleaning_asm_lst_lbls(t_list *lst)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = lst;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(((t_lbl*)ptr2->content)->name);
		free(ptr2->content);
		free(ptr2);
	}
}

void		cleaning_asm_lst_sruct(t_fls *fls)
{
	if (fls->name)
		ft_strdel(&fls->name);
	if (fls->cmnt)
		ft_strdel(&fls->cmnt);
	if (fls->lbls)
		cleaning_asm_lst_lbls(fls->lbls);
	if (fls->lines)
		cleaning_asm_lst_lines(fls->lines);
	if (fls->instr)
		cleaning_asm_lst_instr(fls->instr);
	if (fls->spltd)
		cleaning_asm_lst_spltd(fls->spltd);
	free(fls);
}

void		clean_data_to_file(t_asm *data)
{
	t_asmlst	*file_lst;
	t_asmlst	*temp;
	int			i;

	file_lst = data->next;
	if (data->filename)
		ft_strdel(&data->filename);
	if (data->filecomment)
		ft_strdel(&data->filecomment);
	while (file_lst)
	{
		temp = file_lst;
		if (temp->label)
			ft_strdel(&temp->label);
		if (temp->op_code)
			ft_strdel(&temp->op_code);
		i = -1;
		while (++i < 3)
		{
			if (temp->islabel[i] != NULL)
				ft_strdel(&temp->islabel[i]);
		}
		file_lst = file_lst->next;
		free(temp);
	}
}

void		cleaning_asm_lst(t_list **fl_lst, t_list **fl_err, t_asm *data)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *fl_lst;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		if (tmp2->content)
			cleaning_asm_lst_sruct(tmp2->content);
		free(tmp2);
	}
	tmp = *fl_err;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		if (tmp2->content)
			cleaning_asm_lst_sruct(tmp2->content);
		if (tmp2)
			free(tmp2);
	}
	if (data->filename)
		clean_data_to_file(data);
}

int			print_errors2(char err_type, char *token, char *err_str, int line)
{
	char	*err;

	err = NULL;
	if (err_type == 1)
		err = "Syntax error at token ";
	else if (err_type == 2)
		err = "Invalid argument for ";
	else if (err_type == 0)
		err = "";
	else if (err_type == 3)
		err = "Lexical error ";
	else if (err_type == 4)
		err = "Lexical error at NAME ";
	else if (err_type == 5)
		err = "Lexical error at COMMENT ";
	else if (err_type == 6)
		err = "Invalid instruction at token ";
	ft_printf("%s%s \"%s\" at line %d\n", err, token, err_str, line);
	g_is_err = 1;
	return (0);
}

void				asm_del_lst(t_list **begin)
{
	t_list	*ptr;
	t_list	*ptr2;

	ptr = *begin;
	while (ptr)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		free(ptr2->content);
		free(ptr2);
	}
}

static void			cleaning_asm(t_asm *data)
{
	if (data->dotsname)
		ft_strdel(&data->dotsname);
	if (data->dotcorname)
		ft_strdel(&data->dotcorname);
	if (data->dotsstr)
		ft_strdel(&data->dotsstr);
	if (data->dotsstrtemp)
		ft_strdel(&data->dotsstrtemp);
}

static void			init_data(t_asm *data, char *argv)
{
	data->dotsname = NULL;
	data->dotsstr = NULL;
	data->dotsstrtemp = NULL;
	data->dotcorname = NULL;
	data->fd = -1;
	data->len = ft_strlen(argv);
	data->filename = NULL;
	data->filecomment = NULL;
	data->next = NULL;
}

static int			checkdotcor(t_asm *data, char *argv)
{
	data->dotcorname = ft_strdup(argv);
	data->dotsname = ft_strnew(data->len - 2);
	ft_strncpy(data->dotsname, data->dotcorname, data->len - 3);
	ft_strcpy(ft_strchr(data->dotsname, '.') + 1, "s");
	if ((data->fd = open(data->dotsname, O_RDONLY)) < 0)
		return (1);
	if (ft_strrchr(data->dotsname, '/'))
	{
		argv = ft_strdup(ft_strrchr(data->dotsname, '/') + 1);
		ft_strdel(&data->dotsname);
		data->dotsname = ft_strdup(argv);
		ft_strdel(&argv);
	}
	data->dotsname = ft_strjoin_free(ft_strdup("disasm_"), data->dotsname);
	ft_printf(DDC, data->dotcorname, data->dotsname);
	return (0);
}

static int			checkdots(t_asm *data, char *argv)
{
	t_list		*fl_lst;
	t_list		*fl_err;

	fl_lst = NULL;
	fl_err = NULL;
	data->dotsname = ft_strdup(argv);
	data->dotcorname = ft_strnew(data->len + 2);
	ft_strncpy(data->dotcorname, data->dotsname, data->len - 1);
	ft_strcpy(ft_strchr(data->dotcorname, '.') + 1, "cor");
	if ((data->fd = open(data->dotsname, O_RDONLY)) < 0)
		return (1);
	if (ft_strrchr(data->dotcorname, '/'))
	{
		argv = ft_strdup(ft_strrchr(data->dotcorname, '/') + 1);
		ft_strdel(&data->dotcorname);
		data->dotcorname = ft_strdup(argv);
		ft_strdel(&argv);
	}
	if (save_file(&fl_lst, &fl_err, data->fd))
		if (to_file(&fl_lst, data))
			ft_printf(DDS, data->dotsname, data->dotcorname);
	cleaning_asm_lst(&fl_lst, &fl_err, data);
	return (0);
}

int			main(int argc, char **argv)
{
	t_asm		data;
	int			i;
	int			ret;

	i = 0;
	if ((argc == 2 && ft_strequ(argv[1], "-h")) || argc == 1)
	{
		ft_printf("%s%s%s%s", USAGE);
		exit(42);
	}
	while (++i < argc && *(argv)++)
	{
		init_data(&data, *argv);
		if (data.len > 2 && AR1 == 's' && AR2 == '.')
			ret = checkdots(&data, *argv);
		else if (data.len > 4 && AR)
			ret = checkdotcor(&data, *argv);
		else
			ft_printf("[!] Error! '%s' - invalid filename\n", *argv);
		if (ret)
			ft_printf("[!] Error! '%s' - file not found\n", *argv);
		cleaning_asm(&data);
	}
	system("leaks -quiet asm");
	return (0);
}

