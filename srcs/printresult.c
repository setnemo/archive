/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printresult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				search_max_steps(t_lem *data)
{
	int i;
	int steps;

	i = 2;
	steps = 0;
	while (i < data->how_path * 3)
	{
		if (data->solve_path[i] >= steps)
			steps = data->solve_path[i];
		i += 3;
	}
	return (steps);
}

static t_prnt	*create_path_to_print(t_lem *data)
{
	t_prnt *show;

	if (data->toout == NULL)
	{
		data->toout = (t_prnt*)malloc(sizeof(t_prnt));
		ft_bzero(data->toout, sizeof(t_prnt));
		show = data->toout;
		show->pathshow = ft_new_char_arr(search_max_steps(data));
		show->next = NULL;
	}
	else
	{
		show = data->toout;
		while (show->next)
			show = show->next;
		show->next = (t_prnt*)malloc(sizeof(t_prnt));
		ft_bzero(show->next, sizeof(t_prnt));
		show = show->next;
		show->pathshow = ft_new_char_arr(search_max_steps(data));
		show->next = NULL;
	}
	return (show);
}

static void		put_path_in_show(t_prnt *show, t_lem *data, int i)
{
	t_all	*old;
	int		a;
	int		b;

	old = data->alls;
	a = 0;
	while (a++ < i)
		old = old->next;
	a = 0;
	b = 1;
	while (a < old->len)
	{
		show->pathshow[a] = ft_strdup(data->name_room[old->path[b]]);
		a++;
		b++;
	}
	a = 1 + (i * 3);
	show->howa = data->solve_path[a];
}

static void		search_ants(t_lem *data, int ants[])
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (i < data->how_path * 3)
	{
		ants[j] = (data->solve_path[i]);
		i += 3;
		j++;
	}
}

void			manage_output(t_lem *data)
{
	int		ants[data->how_path];
	int		i;
	t_prnt	*show;
	int		*antsup;

	search_ants(data, ants);
	i = 0;
	while (i < data->how_path)
	{
		if (ants[i] != 0)
		{
			show = create_path_to_print(data);
			put_path_in_show(show, data, i);
		}
		else
			break ;
		i++;
	}
	show =  data->toout;
	// while (show)
	// {
	// 	i = -1;
	// 	ft_printf("NEW PATH!\n");
	// 	while (show->pathshow[++i])
	// 		ft_printf("room: %s\n", show->pathshow[i]);
	// 	ft_printf("how a?: %i!\n", show->howa);
	// 	ft_printf("PATH END!\n\n");
	// 	if (show->next)
	// 		show = show->next;
	// 	else
	// 		break ;
	// }
	antsup = ants;
	manage_output2(data, antsup);
}
