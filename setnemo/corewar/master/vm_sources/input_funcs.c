/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:17:27 by nkolosov          #+#    #+#             */
/*   Updated: 2018/05/19 15:17:28 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

static void	parse_n_flag(t_inpdata *data, char **first_arg)
{
	char	*second_arg;
	int		index;

	data->cur_arg++;
	second_arg = get_arg(data);
	index = ft_atoi(second_arg);
	if (index <= 0 || index > MAX_PLAYERS || g_g.taken_index[index - 1])
		print_usage();
	g_g.players[g_g.num_of_players].index = index - 1;
	g_g.taken_index[index - 1] = 1;
	data->cur_arg++;
	*first_arg = get_arg(data);
}

int			inp_player(t_inpdata *data)
{
	char	*first_arg;
	_Bool	has_n;

	first_arg = get_arg(data);
	has_n = ft_strcmp("-n", first_arg) ? 0 : 1;
	if (has_n)
		parse_n_flag(data, &first_arg);
	if (!ft_strstr(first_arg, ".cor"))
	{
		if (has_n)
			not_a_champion(first_arg);
		else
			return (0);
	}
	if (g_g.num_of_players == MAX_PLAYERS)
		print_usage();
	g_g.players[g_g.num_of_players].filename = first_arg;
	parse_player(first_arg, &g_g.players[g_g.num_of_players]);
	g_g.num_of_players++;
	data->cur_arg++;
	return (1);
}

int			inp_lflag(t_inpdata *data)
{
	static int	calls = 0;
	char		*first_arg;
	char		*second_arg;

	first_arg = get_arg(data);
	if (ft_strcmp("-l", first_arg))
		return (0);
	data->cur_arg++;
	second_arg = get_arg(data);
	if (!ft_strcmp("1", second_arg))
		g_g.log_flag1 = 1;
	else if (!ft_strcmp("2", second_arg))
		g_g.log_flag2 = 1;
	else if (!ft_strcmp("12", second_arg) ||
			!ft_strcmp("21", second_arg))
	{
		g_g.log_flag1 = 1;
		g_g.log_flag2 = 1;
	}
	else
		print_usage();
	data->cur_arg++;
	if (++calls > 1 || g_g.to_visualise)
		print_usage();
	return (1);
}

int			inp_vflag(t_inpdata *data)
{
	static int	calls = 0;
	char		*first_arg;

	first_arg = get_arg(data);
	if (ft_strcmp("-v", first_arg))
		return (0);
	data->cur_arg++;
	g_g.to_visualise = 1;
	if (++calls > 1 || g_g.log_flag2 || g_g.log_flag1)
		print_usage();
	return (1);
}

int			inp_dumpflag(t_inpdata *data)
{
	static int	calls = 0;
	char		*first_arg;
	char		*second_arg;

	first_arg = get_arg(data);
	if (ft_strcmp("-dump", first_arg))
		return (0);
	data->cur_arg++;
	second_arg = get_arg(data);
	if (!(is_number(second_arg)) || (g_g.dump_cycle = ft_atoi(second_arg)) < 0)
		print_usage();
	data->cur_arg++;
	if (++calls > 1)
		print_usage();
	return (1);
}
