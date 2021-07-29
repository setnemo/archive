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

static void	check_game_over(t_data *data)
{
	int all;
	int j;
	int i;

	all = 0;
	i = -1;
	while (++i < data->field)
	{
		j = -1;
		while (++j < data->field)
		{
			if (data->core[i][j] == 0)
				all++;
		}
	}
	if (all == 0)
		game_over(data);
}

void		key_down(t_data *data, int count, int alone, int i)
{
	i = -1;
	count = 0;
	alone = 1;
	data->copy = ft_new_int_matrix(data->field);
	while (++i < data->field)
		ft_memcpy(data->copy[i], data->core[i], sizeof(int) * data->field);
	while (count != data->field - 1)
		mv_numbers_down(data, &count);
	sum_numbers_down(data);
	count = 0;
	while (count != data->field - 1)
		mv_numbers_down(data, &count);
	i = -1;
	while (++i < data->field)
	{
		if (alone && ft_memcmp(data->copy[i],
			data->core[i], sizeof(int) * data->field))
		{
			plus_one(data, 0, 0);
			alone = 0;
		}
		free(data->copy[i]);
	}
	free(data->copy);
	check_game_over(data);
}

void		key_up(t_data *data, int count, int alone, int i)
{
	i = -1;
	count = 0;
	alone = 1;
	data->copy = ft_new_int_matrix(data->field);
	while (++i < data->field)
		ft_memcpy(data->copy[i], data->core[i], sizeof(int) * data->field);
	while (count != data->field - 1)
		mv_numbers_up(data, &count);
	sum_numbers_down(data);
	count = 0;
	while (count != data->field - 1)
		mv_numbers_up(data, &count);
	i = -1;
	while (++i < data->field)
	{
		if (alone && ft_memcmp(data->copy[i],
			data->core[i], sizeof(int) * data->field))
		{
			plus_one(data, 0, 0);
			alone = 0;
		}
		free(data->copy[i]);
	}
	free(data->copy);
	check_game_over(data);
}

void		key_left(t_data *data, int count, int alone, int i)
{
	i = -1;
	count = 0;
	alone = 1;
	data->copy = ft_new_int_matrix(data->field);
	while (++i < data->field)
		ft_memcpy(data->copy[i], data->core[i], sizeof(int) * data->field);
	while (count != data->field - 1)
		mv_numbers_left(data, &count);
	sum_numbers_left(data);
	count = 0;
	while (count != data->field - 1)
		mv_numbers_left(data, &count);
	i = -1;
	while (++i < data->field)
	{
		if (alone && ft_memcmp(data->copy[i],
			data->core[i], sizeof(int) * data->field))
		{
			plus_one(data, 0, 0);
			alone = 0;
		}
		free(data->copy[i]);
	}
	free(data->copy);
	check_game_over(data);
}

void		key_right(t_data *data, int count, int alone, int i)
{
	i = -1;
	count = 0;
	alone = 1;
	data->copy = ft_new_int_matrix(data->field);
	while (++i < data->field)
		ft_memcpy(data->copy[i], data->core[i], sizeof(int) * data->field);
	while (count != data->field - 1)
		mv_numbers_right(data, &count);
	sum_numbers_left(data);
	count = 0;
	while (count != data->field - 1)
		mv_numbers_right(data, &count);
	i = -1;
	while (++i < data->field)
	{
		if (alone && ft_memcmp(data->copy[i],
			data->core[i], sizeof(int) * data->field))
		{
			plus_one(data, 0, 0);
			alone = 0;
		}
		free(data->copy[i]);
	}
	free(data->copy);
	check_game_over(data);
}
