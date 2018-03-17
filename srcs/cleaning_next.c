/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	cleaning_way(t_way *ways)
{
	t_way *temp;

	while (ways)
	{
		free(ways->path);
		if (ways->next)
		{
			temp = ways;
			ways = ways->next;
			free(temp);
		}
		else
		{
			free(ways);
			ways = NULL;
		}
	}
}

static void	cleaning_validcoord(t_lem *data)
{
	int a;

	a = 0;
	while (data->validcoord[a])
	{
		free(data->validcoord[a]);
		a++;
	}
	free(data->validcoord);
	data->validcoord = NULL;
}

void		cleaning_next(t_lem *data)
{
	if (data->way)
		cleaning_way(data->way);
	if (data->validcoord)
		cleaning_validcoord(data);
	if (data->solve_path)
		free(data->solve_path);
	if (data->tmp)
		free(data->tmp);
}
