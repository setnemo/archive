/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:38:13 by apakhomo          #+#    #+#             */
/*   Updated: 2018/07/21 15:38:16 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void		check_size(void)
{
	if (COLS < WIN_WIDTH)
	{
		endwin();
		ft_printf("%s\n", "Too small window width!!!");
		exit(0);
	}
	if (LINES < WIN_HEIGHT)
	{
		endwin();
		ft_printf("%s\n", "Too small window height!!!");
		exit(0);
	}
}


static void	fields_function(t_data *data, int *ch)
{
	check_size();
	get_clear();
	get_field(data, 0);
	get_numbers(data);
	timeout(0);
	*ch = getch();
	usleep(33333);
}

void		game_loop(t_data *data)
{
	int ch;
	int count;

	while (42)
	{
		fields_function(data, &ch);
		count = 0;
		if (ch == KEY_DOWN) {
			while (count != data->field - 1)
				mv_numbers_down(data, &count);
			sum_numbers_down(data);
			count = 0;
			while (count != data->field - 1)
				mv_numbers_down(data, &count);
			plus_one(data, 0, 0);
		}
		if (ch == KEY_UP ) {
			while (count != data->field - 1)
				mv_numbers_up(data, &count);
			sum_numbers_down(data);
			count = 0;
			while (count != data->field - 1)
				mv_numbers_up(data, &count);
			plus_one(data, 0, 0);
		}
		if (ch == KEY_LEFT ) {
			while (count != data->field - 1)
				mv_numbers_left(data, &count);
			sum_numbers_left(data);
			count = 0;
			while (count != data->field - 1)
				mv_numbers_left(data, &count);
			plus_one(data, 0, 0);
		}
		if (ch == KEY_RIGHT) {
			while (count != data->field - 1)
				mv_numbers_right(data, &count);
			sum_numbers_left(data);
			count = 0;
			while (count != data->field - 1)
				mv_numbers_right(data, &count);
			plus_one(data, 0, 0);
		}
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
}