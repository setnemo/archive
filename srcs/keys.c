/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzamyati <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 18:58:12 by vzamyati          #+#    #+#             */
/*   Updated: 2018/07/21 18:58:14 by vzamyati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	key_down(t_data *data)
{
	int	count;

	count = 0;
	while (count != data->field - 1)
		mv_numbers_down(data, &count);
	sum_numbers_down(data);
	count = 0;
	while (count != data->field - 1)
		mv_numbers_down(data, &count);
	plus_one(data, 0, 0);
}

void	key_up(t_data *data)
{
	int	count;

	count = 0;
	while (count != data->field - 1)
		mv_numbers_up(data, &count);
	sum_numbers_down(data);
	count = 0;
	while (count != data->field - 1)
		mv_numbers_up(data, &count);
	plus_one(data, 0, 0);
}

void	key_left(t_data *data)
{
	int	count;

	count = 0;
	while (count != data->field - 1)
		mv_numbers_left(data, &count);
	sum_numbers_left(data);
	count = 0;
	while (count != data->field - 1)
		mv_numbers_left(data, &count);
	plus_one(data, 0, 0);
}

void	key_right(t_data *data)
{
	int	count;

	count = 0;
	while (count != data->field - 1)
		mv_numbers_right(data, &count);
	sum_numbers_left(data);
	count = 0;
	while (count != data->field - 1)
		mv_numbers_right(data, &count);
	plus_one(data, 0, 0);
}
