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
		else
		{
			ft_printf(USAGE);
			cleaning(data);
			system("leaks -quiet lem-in");
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
