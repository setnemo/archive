/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_asm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:30:09 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/27 13:46:10 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_ASM_H
# define CORE_ASM_H
# include "asm.h"
# include "split_line.h"

typedef struct	s_fls
{
	char		isname;
	char		iscmnt;
	char		*name;
	char		*cmnt;
	t_list		*lbls; /*list of labels with links to corresponding instructions
						(labels can be without instr-s) */
	t_list		*lines; //for header
	t_list		*instr; //other significant lines
	t_list		*spltd; //lines splited into labels, instructions, arguments
	int			line;
}				t_fls;

char			g_is_err;

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define INIT_INFO				info = {0, 0, NULL};
# define INIT_FILE				{0, 0, NULL, NULL, NULL, NULL};
# define PROG_NAME_LENGTH       (128)
# define COMMENT_LENGTH         (2048)
# define COREWAR_EXEC_MAGIC     0xea83f3
# define REG_NUMBER				16

int				save_file(t_list **fl_lst, t_list **fl_err, int fd);
void			check_cmnt(t_fls *file, t_list **ptr, int *i);
void			print_errors(int err);
void			inspect_str(char *s, char *chars, int *ii);
void			check_header(t_fls *file);
void			split_labels(t_fls *file, t_list *instr);
int				check_empty(char *str);
void			split_lines(t_fls *file, t_list *instr);
int				check_instructions(t_list *spltd, t_list *lbls);
int				print_errors2(char err_type, char *token, char *err_str,\
	int line);
void			asm_del_lst(t_list **begin);
int				identify_argtype(char *arg, t_list *lbls, char **islbl, int *value);

#endif
