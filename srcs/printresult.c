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

static int		search_max_steps(t_lem *data)
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
	while(a++ < i)
		old = old->next;
	a = 0;
	b = 1;
	while (a < old->len)
	{
		show->pathshow[a] = ft_strdup(data->name_room[old->path[b]]);
		a++;
		b++;
	}
}

static void		search_ants(t_lem *data, int ants[])
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (i < data->how_path * 3)
	{
		ants[j] = data->solve_path[i] * data->solve_path[i - 1];
		i += 3;
		j++;
	}
}


void			manage_output(t_lem *data)
{
	int		ants[data->how_path];
	int		i;
	t_prnt	*show;

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

	i = 0;
	// int roomcount = search_max_steps(data);

	int j;
	show = data->toout;
	j = 0;

	t_tout nrm;
	int *antsup;

	antsup = ants;
	nrm.out = ft_new_char_arr(search_max_steps(data) * 2);
	nrm.roomcount = search_max_steps(data);
	if ((int)data->how_ants < data->how_path)
		data->how_path = data->how_ants;
	norme_output_first(&nrm, data, data->toout, antsup);

	j = 0;
	while (nrm.out[j])
	{
		ft_printf("%s\n", nrm.out[j]);
		free(nrm.out[j]);
		j++;
	}

	show = data->toout;
	clean_lst_out(data->toout, 0);

	free(nrm.out);
	i = 0;
}



