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
# include "../libft/include/libft.h"
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
	char					*islabel[3];
	char					bytecode[3];
	int						value_arg[3];
	int						octal;
	int						labelsize;
	int						opcodevalue;
	int						octalvalue;
	int						listsize[4];
	struct s_asmlst			*next;
}							t_asmlst;

union 						s_byterange{
	unsigned int			num;
    unsigned char			ch2[2];
    unsigned char			ch[4];
}							t_byterange;

void						manage_error(t_asm *data, char error);

void						start_reading_s(t_asm *data);


void						get_listsize(t_asmlst *file_lst);
int							get_octalvalue(char val[]);
int							get_opcodevalue(char *opcode);
int							get_labelsize(char *opcode);
int							get_octal(char *opcode);

void						get_file_lst(t_asmlst *file_lst, t_asm *data,
	int i, int countlst);
void						get_labelvaluesize(t_asmlst *file_lst, char *str,
	int countl, int j);
#endif
