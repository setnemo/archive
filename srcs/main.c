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
# define MIN_WIDTH 10 
# define MIN_HEIGHT 10
// # define FIELD 4

// #define WIN_WIDTH FIELD * 2 + 1
// #define WIN_HEIGHT FIELD * 2 + 1

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

void		get_field()
{
	int i;
	int j;

	i = -1;
	while (++i < COLSFIELD * FIELD + 1)
	{
		j = 0;
		// mvprintw(0, i, "-");
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

int main(int argc, char const *argv[])
{
	if (argv[1] && ft_atoi(argv[1]) > 3)
		FIELD = ft_atoi(argv[1]);
	/* NCURSES START */

	if (!(initscr()))
		ft_printf("Ncurses problem with memory\n");

	curs_set(0);
	// if (COLS < WIN_WIDTH)
	// {
	// 	endwin();
	// 	ft_printf("%s\n", "Too small window width!!! Min width must");
	// 	// exit(0);
	// }
	// if (LINES < WIN_HEIGHT)
	// {
	// 	endwin();
	// 	ft_printf("%s\n", "Too small window height!!! Min height must");
	// 	// exit(0);
	// }
	WINDOW *win = newwin(COLS,LINES, 0, 0);
	start_color();
	colors();
	wattron(win, COLOR_PAIR(21));


	// mvwprintw(win, 0, 0, "X");
	refresh();
	// BORDER PRINT
	attron(COLOR_PAIR(15));
	COLSFIELD = (COLS - 1) / FIELD;
	LINESFIELD = (LINES - 1) / FIELD;
	// ft_printf("COL[%d], FIELD[%d], ALL_SYMBOL[%d], COLSFIELD[%d]", COLS, FIELD, COLS - 1, COLSFIELD);
	get_field();
	// for (int i = 0; i < 10; ++i)
	// {
	// 	mvprintw(0,i, "X");
	// 	/* code */
	// }
	// mvprintw("blabla");
	// box(win, 0, 0);

	wrefresh(win);
	getch();
	noecho();
	cbreak(); 
	delwin(win);
	endwin();




	// get screen size;
	//int yMAX, xMAX;
	//getmaxyx(stdscr, yMAX, xMAX);
	 // create the window for the output;
	//WINDOW *game_board = newwin(yMAX, xMAX, 0, 0);
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



	return 0;
}