/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:26:19 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/01 14:26:19 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*g_win;
void	*g_mlx;

void drawLine(int x1, int y1, int x2, int y2)
{
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	mlx_pixel_put(g_mlx, g_win, x2, y2, 0xFFFFFF);
	while(x1 != x2 || y1 != y2) 
	{
		mlx_pixel_put(g_mlx, g_win, x1, y1, 0xFFFFFF);
		int error2 = error * 2;
		//
		if(error2 > -deltaY) 
		{
			error -= deltaY;
			x1 += signX;
		}
		if(error2 < deltaX) 
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

int     main(int argc, char **argv)
{
	t_mlx   *fdf;
	int     fd;

	g_mlx = mlx_init();
	g_win = mlx_new_window(g_mlx, 500, 500, "fdf 42");
	if (argc == 2 && argv)
	{
		fdf = (t_mlx*)malloc(sizeof(t_mlx));
		fd = open(argv[1], O_RDONLY);
		read_map(fdf, fd);
//      ft_printf("test fdf\n");
		close(fd);
	}
	int a = 10;
	int b = 10;
	while (a < 400)
	{
		b = 10;
		while (b < 400)
		{
			drawLine(a + 10, b, a, b); //hor
			drawLine(a, b + 10, a, b); //vert
			b +=10;
			//drawLine(a, b, a, b); //vert
		}
		a += 10;
		drawLine(a - 10, b, a, b); //horiz
		drawLine(a, b - 10, a, b); // vert
	}
	mlx_loop(g_mlx);
	return (0);
}
