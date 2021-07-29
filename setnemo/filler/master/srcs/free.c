/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		free_bit(t_fill *game)
{
	int a;

	a = 0;
	while (a < game->bit_size[0])
	{
		ft_strdel(&game->bit[a]);
		a++;
	}
	free(game->bit);
}

void		free_map(t_fill *game)
{
	int a;

	a = 0;
	while (a < game->map_size[0])
	{
		ft_strdel(&game->map[a]);
		a++;
	}
	free(game->map);
}

void		free_sptlist(t_spt *lstsp)
{
	t_spt	*temp;

	while (lstsp)
	{
		if (lstsp->next)
		{
			temp = lstsp->next;
			free(lstsp);
			lstsp = temp;
		}
		else
			break ;
	}
	free(lstsp);
}

void		free_bitlist(t_bit *lstsp)
{
	t_bit	*temp;

	while (lstsp)
	{
		if (lstsp->next)
		{
			temp = lstsp->next;
			free(lstsp);
			lstsp = temp;
		}
		else
			break ;
	}
	free(lstsp);
}
