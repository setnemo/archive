/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:51:23 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/30 15:51:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "../asm_libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct				s_asm
{
	size_t					len;
	int						fd;
	char					*dotsname;
	char					*dotsstr;
	char					*dotsstrtemp;
	int						dotcorfd;
	int						allbytes;
	char					*dotcorname;
	char					*filename;
	char					*filecomment;
	struct s_asmlst			*next;
}							t_asm;

typedef struct				s_asmlst
{
	char					*label;
	char					*op_code;
	int						count_arg;
	int						empty;
	char					*islabel[3];
	char					bytecode[3];
	int						value_arg[3];
	int						octal;
	int						labelsize;
	int						opcodevalue;
	int						octalvalue;
	int						listsize[4];
	int						number;
	struct s_asmlst			*next;
	struct s_asmlst			*prev;
}							t_asmlst;

union						u_byterange
{
	int						num;
	char					ch2[2];
	char					ch[4];
}							t_byterange;

void						manage_error(t_asm *data, char error);

void						start_reading_s(t_asm *data);

void						get_listsize(t_asmlst *file_lst);
int							get_octalvalue(char val[]);
int							get_opcodevalue(char *opcode);
int							get_labelsize(char *opcode);
int							get_octal(char *opcode);

void						get_file_lst(t_asm *data,
	int i, int countlst);
void						get_labelvaluesize(t_asmlst *file_lst, char *str,
	int countl, int j);

int							setfixsize(t_asmlst *file_lst, int j);
void						get_labelvaluesize(t_asmlst *file_lst, char *str,
	int countl, int j);
int							push_data_to_file(t_asm *data);

#endif
