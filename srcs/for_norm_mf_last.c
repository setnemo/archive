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

// #include "lemin.h"
// #define N nrm
// #define NO N->out
// #define SJF ft_strjoin_free

// static void		nrm_out_write(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
// {
// 	if (ants[N->cc] == 0)
// 	{
// 		test = data->toout;
// 		return ;
// 	}
// 	if (N->i + N->cc == (int)data->how_ants)
// 		return ;
// 	if (N->j == N->cc && N->j == 0)
// 	{
// 		ants[N->cc]--;
// 		// if (ants[N->cc] == 0)
// 		// 	return ;
// 	}
// 	if (NO[N->j] == NULL)
// 		NO[N->j] = ft_strdup("L");
// 	else
// 		NO[N->j] = SJF(NO[N->j], ft_strdup(" L"));
// 	NO[N->j] = SJF(NO[N->j], ft_itoa(N->i + N->cc + 1));
// 	NO[N->j] = SJF(NO[N->j], ft_strdup("-"));
// 	NO[N->j] = SJF(NO[N->j], ft_strdup(test->pathshow[N->k]));
// 	N->k++;
// 	if ((N->i + N->cc + 1) % data->how_path == 0)
// 		N->jc++;
// 	ft_printf("///%i\n",N->jc);
// 	//ft_printf("%i[%i]\n",N->cc,ants[N->cc]);
// 	N->check++;
// }

// static int		elseifinwhile(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
// {
// 	N->check++;
// 	if (ants[N->cc] == 0)
// 	{
// 		N->cc++;
// 		test = data->toout;
// 		return (1);
// 	}
// 	else
// 	{
// 		if (test->next)
// 			test = test->next;
// 		else
// 			test = data->toout;
// 	}
// 	N->cc++;
// 	N->next = test;
// 	return (0);
// }

// static int		firstifinwhile(t_tout *nrm, t_prnt *test,
// 	int *ants, t_lem *data)
// {
// 	nrm_out_write(nrm, test, ants, data);
// 	if (ants[N->cc] == 0)
// 	{
// 		test = data->toout;
// 		N->cc++;
// 		return (1);
// 	}
// 	else
// 	{
// 		if (test->next)
// 			test = test->next;
// 		else
// 			test = data->toout;
// 	}
// 	N->cc++;
// 	N->next = test;
// 	return (0);
// }

// static void		one_while(t_tout *nrm, t_prnt *test, int *ants, t_lem *data)
// {
// 	while (N->k <N->linecount)
// 	{
// 		if (test->pathshow[N->j])
// 		{
// 			if (firstifinwhile(nrm, test, ants, data))
// 			{
// 				test = N->next;
// 				break ;
// 			}
// 			test = N->next;
// 		}
// 		else
// 		{
// 			if (elseifinwhile(nrm, test, ants, data))
// 			{
// 				test = N->next;
// 				break ;
// 			}
// 			test = N->next;
// 		}
// 		if (N->check == data->how_path)
// 		{
// 			BRK((test = data->toout));
// 		}
// 	}
// }

// void			norme_output_first(t_tout *nrm, t_lem *data,
// 	t_prnt *test, int *ants)
// {
// 	N->jc =0;
// 	init_nrm(nrm, 0);
// 	while (N->i < (int)data->how_ants)
// 	{
// 		N->j = 0 + N->jc;
// 		ft_printf("{{%i}}\n",N->j);
// 		while (N->j < N->roomcount)
// 		{
// 			N->k = 0;
// 			init_nrm(nrm, 1);
// 			one_while(nrm, test, ants, data);
// 			N->j++;
// 		}
// 		init_nrm(nrm, 2);
// 	}
// }
