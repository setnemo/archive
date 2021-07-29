/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm_mf_last.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "showinfo.h"

static int		search_all_steps(t_lem *data)
{
	int i;
	int steps;

	i = 2;
	steps = 0;
	while (i < data->how_path * 3)
	{
		if (data->solve_path[i - 1] != 0)
			steps += data->solve_path[i - 2] *
		data->solve_path[i - 1];
		i += 3;
	}
	return (steps);
}

static void		print_all_path(t_lem *data)
{
	t_prnt	*show;
	int		i;
	int		j;

	show = data->toout;
	j = 1;
	ft_printf("All path (without start room name)\n");
	while (show)
	{
		i = -1;
		ft_printf("Path %i  ", j++);
		while (show->pathshow[++i])
			ft_printf("[%s] ", show->pathshow[i]);
		ft_printf("\n", show->howa);
		if (show->next)
			show = show->next;
		else
			break ;
	}
}

static void		print_info(t_lem *data, int i, int j)
{
	if (data->oneway)
	{
		ft_printf(SI00, search_min_steps(data));
		ft_printf(SI01, (search_min_steps(data) + data->how_ants) - 1);
		ft_printf(SI02, search_min_steps(data) * data->how_ants);
	}
	else
	{
		ft_printf(SI03, search_min_steps(data));
		ft_printf(SI04, search_max_steps2(data));
		ft_printf(SI05, data->howprintlines);
		ft_printf(SI06, search_all_steps(data));
		ft_printf("%s%s", SI07);
		while (j < data->how_path * 3)
		{
			ft_printf(SI10, i + 1, data->solve_path[j],
				data->solve_path[j + 1]);
			i++;
			j += 3;
		}
		print_all_path(data);
	}
}

static void		clean_lst_out(t_prnt *show, int i)
{
	t_prnt	*temp;

	while (show)
	{
		if (show->pathshow)
		{
			i = 0;
			while (show->pathshow[i])
				free(show->pathshow[i++]);
			free(show->pathshow);
		}
		if (show->next)
		{
			temp = show;
			show = show->next;
			free(temp);
		}
		else
		{
			free(show);
			break ;
		}
	}
}

void			manage_output2(t_lem *data)
{
	t_tout	nrm;
	int		j;

	ft_bzero(&nrm, sizeof(t_tout));
	nrm.out = ft_new_char_arr(search_max_steps(data) *
		search_max_steps(data));
	nrm.linecount = search_max_steps(data);
	if (data->oneway == 1)
		data->how_path = 1;
	output_first(&nrm, data, data->toout);
	j = 0;
	ft_printf("%s\n", data->input);
	while (nrm.out[j])
	{
		ft_printf("%s\n", nrm.out[j]);
		free(nrm.out[j]);
		j++;
	}
	data->howprintlines = j;
	if (data->info)
		print_info(data, 0, 0);
	clean_lst_out(data->toout, 0);
	free(nrm.out);
}
