/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <apakhomo@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 10:23:57 by apakhomo          #+#    #+#             */
/*   Updated: 2018/07/21 10:24:04 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
# define MIN_WIDTH 10 
# define MIN_HEIGHT 10
// # define FIELD 4

#define WIN_WIDTH 21
#define WIN_HEIGHT 21
#define RAND4 20

int FIELD = 4; 
int COLSFIELD = 0; 
int LINESFIELD = 0; 

void	colors(void)
{
	init_color(COLOR_WHITE, 300, 300, 300);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(21, COLOR_BLACK, COLOR_GREEN);
	init_pair(31, COLOR_WHITE, COLOR_GREEN);
	init_pair(22, COLOR_BLACK, COLOR_RED);
	init_pair(32, COLOR_WHITE, COLOR_RED);
	init_pair(23, COLOR_BLACK, COLOR_YELLOW);
	init_pair(33, COLOR_WHITE, COLOR_YELLOW);
	init_pair(24, COLOR_BLACK, COLOR_BLUE);
	init_pair(34, COLOR_WHITE, COLOR_BLUE);
	init_pair(14, COLOR_WHITE, COLOR_BLACK);
	init_pair(41, COLOR_BLACK, COLOR_WHITE);
	init_pair(15, COLOR_WHITE, COLOR_BLACK);
	init_pair(17, COLOR_BLACK, COLOR_BLACK); //затирать
	init_pair(18, COLOR_WHITE, COLOR_WHITE);
}

void		get_numbers(t_data *data)
{
	int i;
	int j;
	char *temp;

	i = -1;
	while (++i < FIELD)
	{
		j = -1;
		while (++j < FIELD)
		{
			temp = ft_itoa(data->core[i][j]);
			mvprintw(LINESFIELD/2 + i * LINESFIELD, COLSFIELD/2 + j * COLSFIELD, temp);
			ft_strdel(&temp);
		}
	}
}

void		get_field()
{
	int i;
	int j;

	i = -1;
	while (++i < COLSFIELD * FIELD + 1)
	{
		j = 0;
		while (j < LINESFIELD * FIELD + 1)
		{
			if (i % COLSFIELD == 0)
			{
				if (j % LINESFIELD == 0)
					mvprintw(j, i, "+");
				else
					mvprintw(j, i, "|");
			}
			else if (j % LINESFIELD == 0)
				mvprintw(j, i, "-");
			else
				mvprintw(j, i, " ");
			j++;
		}
	}
}

int			mv_numbers_down(t_data *data)
{
	return (0);
}

int			mv_numbers_up(t_data *data)
{
	return (0);
}

int			mv_numbers_left(t_data *data)
{
	return (0);
}

int			mv_numbers_right(t_data *data)
{
	return (0);
}

int main(int argc, char const *argv[])
{
	if (argv[1] && ft_atoi(argv[1]) > 3)
		FIELD = ft_atoi(argv[1]);
	/* NCURSES START */

	if (!(initscr()))
		ft_printf("Ncurses problem with memory\n");

	curs_set(0);
	WINDOW *win = newwin(COLS,LINES, 0, 0);
	if (COLS < WIN_WIDTH)
	{
		endwin();
		ft_printf("%s\n", "Too small window width!!! Min width must");
		exit(0);
	}
	if (LINES < WIN_HEIGHT)
	{
		endwin();
		ft_printf("%s\n", "Too small window height!!! Min height must");
		exit(0);
	}
	start_color();
	colors();
	// wattron(win, COLOR_PAIR(21));


	// mvwprintw(win, 0, 0, "X");
	noecho();
	cbreak(); 
	refresh();
	keypad(stdscr, TRUE);
	// BORDER PRINT
	attron(COLOR_PAIR(15));
	// ft_printf("COL[%d], FIELD[%d], ALL_SYMBOL[%d], COLSFIELD[%d]", COLS, FIELD, COLS - 1, COLSFIELD);
	int random4[100];
	for (int i = 0; i < 100; ++i)
	{
		random4[i] = 2;
	}
	for (int i = 0; i < RAND4; ++i)
	{
		random4[i] = 4;
	}
	t_data data;
	data.core = ft_new_int_matrix(FIELD);
	int i = -1;
	int j;
	srand(time(NULL));
	char *test1, *test2, *test3, *test4;
	COLSFIELD = (COLS - 1) / FIELD;
	LINESFIELD = (LINES - 1) / FIELD;
	get_field();
	data.core[rand() % FIELD][rand() % FIELD] = random4[rand() % 100];
	data.core[rand() % FIELD][rand() % FIELD] = random4[rand() % 100];
	get_numbers(&data);
	int ch;
	char *str;
	while (42)
	{
		if (COLS < WIN_WIDTH)
		{
			endwin();
			ft_printf("%s\n", "Too small window width!!! Min width must");
			exit(0);
		}
		if (LINES < WIN_HEIGHT)
		{
			endwin();
			ft_printf("%s\n", "Too small window height!!! Min height must");
			exit(0);
		}
		COLSFIELD = (COLS - 1) / FIELD;
		LINESFIELD = (LINES - 1) / FIELD;
		get_field();
		get_numbers(&data);
		// mvprintw(4, 2, "ž");
		wrefresh(win);
		timeout(0);
		// ch = 0;
		ch = getch();
		usleep(33333);
		// mvprintw( 2,  2, str);
		if (ch == KEY_DOWN) {
			// ft_printf("%s\n", "KEY_DOWN");
			// mvprintw( 2,  2, str);
			// mvprintw( 5,  5, "KEY_DOWN   ");
			mv_numbers_down(&data);
		}
		if (ch == KEY_UP ) {
			// ft_printf("%s\n", "KEY_UP");
			// mvprintw( 2,  2, str);
			// mvprintw( 5,  5, "KEY_UP     ");
			mv_numbers_up(&data);
		}
		if (ch == KEY_LEFT ) {
			// ft_printf("%s\n", "KEY_LEFT");
			// mvprintw( 2,  2, str);
			// mvprintw( 5,  5, "KEY_LEFT   ");
			mv_numbers_left(&data);
		}
		if (ch == KEY_RIGHT) {
			// ft_printf("%s\n", "KEY_RIGHT");
			// mvprintw( 2,  2, str);
			// mvprintw( 5,  5, "KEY_RIGHT  ");
			mv_numbers_right(&data);
		}
		if (ch == 27)
		{
			endwin();
			break ;
		// ft_printf("ch[%d]\n", ch);
		}
		
	}
	
	// for (int i = 0; i < 10; ++i)
	// {
	// 	mvprintw(0,i, "X");
	// 	/* code */
	// }
	// mvprintw("blabla");
	// box(win, 0, 0);

	delwin(win);
	endwin();



	system("leaks -quiet game_2048");
	// get screen size;
	//int yMAX, xMAX;
	//getmaxyx(stdscr, yMAX, xMAX);
	 // create the window for the output;
	//WINDOW *game_board = newwin(yMAX, xMAX, 1, 10);
	//refresh();

	//box(game_board, 0, 0);
	//wrefresh(game_board);

	// Player Destroyer(100, "Destroyer");

	// Destroyer.PrintPlayer(game_board);
	//mvwprintw(game_board, 1, 1, "X");
	//wprintw(game_board, "1", "1");
	//wrefresh(game_board);

	//getch();

	//endwin();



// void Window::Print ( WINDOW * var )
// {
//  mvwprintw(var, this->_coord_x, this->_coord_y, "X");

// }



	return (0);
}