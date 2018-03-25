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
#define N nrm
#define NO N->out
#define SJF ft_strjoin_free

static void		nrm_out_write(t_tout *nrm, t_prnt *test, int *ants)
{
	if (NO[N->j + N->k] == NULL)
		NO[N->j + N->k] = ft_strdup("L");
	else
		NO[N->j + N->k] = SJF(NO[N->j + N->k], ft_strdup(" L"));
	NO[N->j + N->k] = SJF(NO[N->j + N->k], ft_itoa(N->i + N->cc + 1));
	NO[N->j + N->k] = SJF(NO[N->j + N->k], ft_strdup("-"));
	NO[N->j + N->k] = SJF(NO[N->j + N->k], ft_strdup(test->pathshow[N->j]));
	ants[N->cc]--;
	N->check++;
}

static int		elseifinwhile(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
{
	N->check++;
	if (ants[N->cc] <= 0)
	{
		N->cc++;
		test = data->toout;
		return (1);
	}
	else
		test = test->next;
	N->cc++;
	N->next = test;
	return (0);
}

static int		firstifinwhile(t_tout *nrm, t_prnt *test,
	int *ants, t_lem *data)
{
	nrm_out_write(nrm, test, ants);
	if (ants[N->cc] <= 0)
	{
		test = data->toout;
		N->cc++;
		return (1);
	}
	else
		test = test->next;
	N->cc++;
	N->next = test;
	return (0);
}

static void		one_while(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
{
	while (1)
	{
		if (test->pathshow[N->j])
		{
			if (firstifinwhile(nrm, test, ants, data))
			{
				test = N->next;
				break ;
			}
			test = N->next;
		}
		else
		{
			if (elseifinwhile(nrm, test, ants, data))
			{
				test = N->next;
				break ;
			}
			test = N->next;
		}
		if (N->check == data->how_path)
		{
			test = data->toout;
			break ;
		}
	}
}

void			norme_output_first(t_tout *nrm, t_lem *data,
	t_prnt *test, int *ants)
{
	init_nrm(nrm, 0);
	while (N->i < (int)data->how_ants)
	{
		N->j = 0;
		while (N->j < N->roomcount)
		{
			init_nrm(nrm, 1);
			one_while(nrm, test, ants, data);
			N->j++;
		}
		init_nrm(nrm, 2);
	}
}
