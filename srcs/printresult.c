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
		// ft_printf("....................\n");
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
		// ft_printf("...........2.........\n");
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
		ants[j] = data->solve_path[i];
		i += 3;
		j++;
	}
}

// void 	write_first_ants(t_prnt *show, char **out, int j, int i, t_lem *data)
// {
// 	int a;

// 	a = i;
// 	if (i == 0)
// 	{

// 	}
// 	else
// 	{
// 		a = (a + 1) % data->how_path;
// 		while (a)
// 		{
// 			show = show->next;
// 			a--;
// 		}
// 		if (show->pathshow[j])
// 		{
// 			out[j] = ft_strjoin_free(out[j], ft_strdup(" L"));
// 			out[j] = ft_strjoin_free(out[j], ft_itoa(i));
// 			out[j] = ft_strjoin_free(out[j], ft_strdup("-"));
// 			out[j] = ft_strjoin_free(out[j], ft_strdup(show->pathshow[j]));
// 		}
// 	}
// }

void			manage_output(t_lem *data)
{
	int		ants[data->how_path];
	int		i;
	t_prnt	*show;
	char	**out;

	search_ants(data, ants);
	i = 0;
	out = ft_new_char_arr(search_max_steps(data));
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
	show = data->toout;
	for (int i = 0; i < data->how_path; ++i)
		ft_printf("[%i] ", ants[i]);
	ft_printf("\n");
	while (show)
	{
		for (int i = 0; show->pathshow[i]; ++i)
			ft_printf("%s ", show->pathshow[i]);
		ft_printf("\n");
		if (show->next)
			show = show->next;
		else
			break ;
	}

	i = 0;
	int roomcount = search_max_steps(data);
	// while (i < (int)data->how_ants)
	// {
	// 	while (j < roomcount)
	// 	{

	// 	}
	int j;
	show = data->toout;
	j = 0;
	t_prnt	*test;
	int k;

	k = 0;
	int check;

	int cc;
	test = data->toout;
	while (i < (int)data->how_ants)
	{
		j = k;
		while (j < roomcount)
		{
			check = 0;
			cc = 0;
			while (1)
			{
				if (test->pathshow[j])
				{
					if (out[j] == NULL)
						out[j] = ft_strdup("L");
					else
						out[j] = ft_strjoin_free(out[j], ft_strdup(" L"));
					out[j] = ft_strjoin_free(out[j], ft_itoa(i + cc));
					out[j] = ft_strjoin_free(out[j], ft_strdup("-"));
					out[j] = ft_strjoin_free(out[j], ft_strdup(test->pathshow[j]));
					check++;
					cc++;
					test = test->next;
					//ft_printf("%s\n", out[j]);
				}
				else if (j < roomcount)
				{
					test = test->next;
					check++;
				}
				if (check == data->how_path)
				{
					k++;
					test = data->toout;
					break ;
				}
			}
			j++;
		}
		i++;
	}

	j = 0;
	while (j < roomcount)
		ft_printf("%s\n", out[j++]);

	show = data->toout;
	clean_lst_out(data->toout, 0);
	free(out[0]);
	free(out[1]);
	free(out[2]);
	free(out[3]);
	free(out);
	i = 0;
}



