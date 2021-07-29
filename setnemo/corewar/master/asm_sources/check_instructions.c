/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:58:36 by oantonen          #+#    #+#             */
/*   Updated: 2018/05/05 22:32:01 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "op.h"
#define IDARG (char*)ptr->content, lbls, &line->islbl[i], &line->value[i]

int		check_args(t_spl *line, t_list *args, char arg_type[3], t_list *lbls)
{
	t_list	*ptr;
	int		arg;
	int		i;

	i = 0;
	ptr = args;
	while (ptr && !g_is_err)
	{
		arg = identify_argtype(IDARG);
		if (arg == 0 || (arg != ISREG && arg != ISDIR && arg != ISIND))
			print_errors2(2, line->op_code, (char*)ptr->content, line->ln_nb);
		if (arg == 1 || arg == 2)
			line->bc[i] = arg;
		if (arg == 4)
			line->bc[i] = 3;
		ptr = ptr->next;
		i++;
	}
	return (1);
}

int		check_opcode(t_spl *spltd)
{
	char	*ins;
	int		i;

	ins = spltd->op_code;
	i = 0;
	if (ins == NULL)
		return (-1);
	while (g_optab[i].name)
	{
		if (ft_strequ(spltd->op_code, g_optab[i].name))
			break ;
		i++;
	}
	if (i == 16)
		print_errors2(6, "[INSTRUCTION]", ins, spltd->ln_nb);
	else if (spltd->q_arg != g_optab[i].q_arg)
		print_errors2(1, "[ARGUMENTS]", "№ of args don't match", spltd->ln_nb);
	return (i);
}

int		check_instructions(t_list *spltd, t_list *lbls)
{
	t_list	*ptr;
	t_spl	*line;
	int		op_nb;

	ptr = spltd;
	while (ptr)
	{
		line = (t_spl*)ptr->content;
		if (line->op_code)
			op_nb = check_opcode(line);
		if (!g_is_err && op_nb != -1)
			op_nb = check_args(line, line->args, g_optab[op_nb].arg_type, lbls);
		if (g_is_err)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}
