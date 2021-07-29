/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm_mf_last2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define TPSHNN test->pathshow[nrm->name]
#define NONLNC nrm->out[nrm->line + nrm->correct]

static t_prnt	*returntestlist(t_prnt *show, int *i)
{
	if (show->next)
	{
		while ((*i)-- && show->next->howa)
		{
			if (show->next)
				show = show->next;
			else
				break ;
		}
	}
	return (show);
}

static void		whileinwhile(t_tout *nrm, t_prnt *test)
{
	while (nrm->line < nrm->linecount)
	{
		if (TPSHNN)
		{
			if (nrm->name == 0)
			{
				nrm->path++;
				test->howa--;
			}
			if (NONLNC == NULL)
				NONLNC = ft_strdup("L");
			else
				NONLNC = ft_strjoin_free(NONLNC, ft_strdup(" L"));
			NONLNC = ft_strjoin_free(NONLNC, ft_itoa(nrm->ant + 1));
			NONLNC = ft_strjoin_free(NONLNC, ft_strdup("-"));
			NONLNC = ft_strjoin_free(NONLNC, ft_strdup(TPSHNN));
		}
		nrm->line++;
		nrm->name++;
	}
}

void			output_first(t_tout *nrm, t_lem *data, t_prnt *test)
{
	int mod;

	nrm->ant = 0;
	nrm->correct = 0;
	nrm->path = 0;
	while (nrm->ant < (int)data->how_ants)
	{
		mod = nrm->ant % data->how_path;
		test = returntestlist(data->toout, &mod);
		if (mod > 0)
			nrm->correct++;
		nrm->line = 0;
		nrm->name = 0;
		whileinwhile(nrm, test);
		if (nrm->path == data->how_path)
		{
			nrm->path = 0;
			nrm->correct++;
		}
		if (data->how_path == 1)
			if (test->pathshow[1] == NULL)
				nrm->correct = 0;
		nrm->ant++;
	}
}
