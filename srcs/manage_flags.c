/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define USAGE "%s%s%s", USAGE1, USAGE2, USAGE3
#define USAGE1 "usage: ./lemin [flag1] [flagN] [redirect file, use '<']\n"
#define USAGE2 "               -e       Error managment\n"
#define USAGE3 "               -s       Print input string if error in data\n"

void			set_flags(t_lem *data, char **argv, int flags)
{
	int i;

	i = 0;
	while (i < flags)
	{
		if (ft_strequ(argv[i], "-e"))
			data->error = 1;
		else if (ft_strequ(argv[i], "-s"))
			data->showinput = 1;
		else if (ft_strequ(argv[i], "-algo"))
			data->algo = 1;
		else
		{
			ft_printf(USAGE);
			cleaning(data);
			exit(-42);
		}
		i++;
	}
}

void			init_nrm(t_tout *nrm, int flag)
{
	if (flag)
	{
		if (flag == 1)
		{
			nrm->check = 0;
			nrm->cc = 0;
		}
		else if (flag == 2)
		{
			nrm->k++;
			nrm->i += nrm->cc;
		}
	}
	else
	{
		nrm->i = 0;
		nrm->k = 0;
		nrm->check = 0;
		nrm->cc = 0;
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

void			manage_output2(t_lem *data, int *ants)
{
	t_tout	nrm;
	int		j;

	nrm.out = ft_new_char_arr(search_max_steps(data) * 2);
	nrm.roomcount = search_max_steps(data);
	// if ((int)data->how_ants < data->how_path)
	// 	data->how_path = data->how_ants;
	// if (data->algo == 0)
	// 	data->how_path = 1;
	norme_output_first(&nrm, data, data->toout, ants);
	j = 0;
	while (nrm.out[j])
	{
		ft_printf("%s\n", nrm.out[j]);
		free(nrm.out[j]);
		j++;
	}
	clean_lst_out(data->toout, 0);
	free(nrm.out);
}
