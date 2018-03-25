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

static void		init_nrm(t_tout *nrm, int flag)
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

static void		one_while(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
{
	while (1)
	{
		if (test->pathshow[nrm->j])
		{
			nrm_out_write(nrm, test, ants);
			if (ants[nrm->cc] <= 0)
			{
				test = data->toout;
				nrm->cc++;
				break ;
			}
			else
				test = test->next;
			nrm->cc++;
		}
		else
		{
			nrm->check++;
			if (ants[nrm->cc] <= 0)
			{
				nrm->cc++;
				test = data->toout;
				break ;
			}
			else
				test = test->next;
			nrm->cc++;
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
