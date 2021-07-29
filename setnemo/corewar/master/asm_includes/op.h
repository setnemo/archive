/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:27:14 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/26 18:08:17 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define T_REG	1
# define T_DIR	2
# define T_IND	4
# define ISREG	((arg_type[i] >> 0) & 1U)
# define ISDIR	((arg_type[i] ) & 2U)
# define ISIND	((arg_type[i] ) & 4U)

typedef struct	s_op
{
	char		*name;
	char		q_arg;
	char		arg_type[3];
	char		op_code;
	int			cycles;
	char		*descr;
	char		codage;
	char		carry;

}				t_op;

t_op	g_optab[17];

#endif
