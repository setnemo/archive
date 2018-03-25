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

static void		nrm_out_write(t_tout *nrm, t_prnt *test, int *ants)
{
	if (nrm->out[nrm->j + nrm->k] == NULL)
		nrm->out[nrm->j + nrm->k] = ft_strdup("L");
	else
		nrm->out[nrm->j + nrm->k] = ft_strjoin_free(nrm->out[nrm->j + nrm->k], ft_strdup(" L"));
	nrm->out[nrm->j + nrm->k] = ft_strjoin_free(nrm->out[nrm->j + nrm->k], ft_itoa(nrm->i + nrm->cc + 1));
	nrm->out[nrm->j + nrm->k] = ft_strjoin_free(nrm->out[nrm->j + nrm->k], ft_strdup("-"));
	nrm->out[nrm->j + nrm->k] = ft_strjoin_free(nrm->out[nrm->j + nrm->k], ft_strdup(test->pathshow[nrm->j]));
	ants[nrm->cc]--;
	nrm->check++;
}

static int		elseifinwhile(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
{
	nrm->check++;
	if (ants[nrm->cc] <= 0)
	{
		nrm->cc++;
		test = data->toout;
		return (1);
	}
	else
		test = test->next;
	nrm->cc++;
	nrm->next = test;
	return (0);
}

static int		firstifinwhile(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
{
	nrm_out_write(nrm, test, ants);
	if (ants[nrm->cc] <= 0)
	{
		test = data->toout;
		nrm->cc++;
		return (1);
	}
	else
		test = test->next;
	nrm->cc++;
	nrm->next = test;
	return (0);
}

static void		one_while(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
{
	while (1)
	{
		if (test->pathshow[nrm->j])
		{	
			if (firstifinwhile(nrm, test, ants, data))
			{
				test = nrm->next;
				break ;
			}
		}
		else
		{
			if (elseifinwhile(nrm, test, ants, data))
			{
				test = nrm->next;
				break ;
			}
		}
		if (nrm->check == data->how_path)
		{
			test = data->toout;
			break ;
		}
	}
}

void			norme_output_first(t_tout *nrm, t_lem *data, t_prnt *test, int *ants)
{
	init_nrm(nrm, 0);
	while (nrm->i < (int)data->how_ants)
	{
		nrm->j = 0;
		while (nrm->j < nrm->roomcount)
		{
			init_nrm(nrm, 1);
			one_while(nrm, test, ants, data);
			nrm->j++;
		}
		init_nrm(nrm, 2);
	}
}
