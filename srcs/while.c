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
		ch == KEY_DOWN ? key_down(data) : 0;
		ch == KEY_UP ? key_up(data) : 0;
		ch == KEY_LEFT ? key_left(data) : 0;
		ch == KEY_RIGHT ? key_right(data) : 0;
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}
}
