/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:35:38 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/15 17:35:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;
extern t_inpf	g_inpfuncs[];

int			inp_sflag(t_inpdata *data)
{
	static int	calls = 0;
	char		*first_arg;

	first_arg = get_arg(data);
	if (ft_strcmp("-s", first_arg))
		return (0);
	data->cur_arg++;
	g_g.silent_live = 1;
	if (++calls > 1)
		print_usage();
	return (1);
}

char		*get_arg(t_inpdata *data)
{
	if (data->cur_arg >= data->ac || data->cur_arg <= 0)
		print_usage();
	return (data->av[data->cur_arg]);
}

void		parse_input(int ac, char **av)
{
	t_inpdata	*data;
	int			i;

	if (ac == 1)
		print_usage();
	MALL(data = (t_inpdata*)ft_memalloc(sizeof(t_inpdata)));
	data->cur_arg = 1;
	data->ac = ac;
	data->av = av;
	while (data->cur_arg < ac)
	{
		i = -1;
		while (++i < NUMOF_INP_FUNCS)
			if ((*g_inpfuncs[i])(data))
				break ;
		if (i == NUMOF_INP_FUNCS)
			invalid_flag(get_arg(data));
	}
	if (g_g.num_of_players == 0)
		print_usage();
}
