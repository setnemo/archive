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

void drawLine(int x1, int y1, int x2, int y2) {

}

int     main(int argc, char **argv)
{
	t_mlx   *fdf;
	int     fd;
	void    *win;
	void    *mlx;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 500, 500, "fdf 42");
	if (argc == 2 && argv)
	{
		fdf = (t_mlx*)malloc(sizeof(t_mlx));
		fd = open(argv[1], O_RDONLY);
		read_map(fdf, fd);
//      ft_printf("test fdf\n");
		close(fd);
	}
	int x1 = 300;
	int y1 = 300;
	int x2 = 100;
	int y2 = 300;
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	mlx_pixel_put(mlx, win, x2, y2, 0xFFFFFF);
	while(x1 != x2 || y1 != y2) 
	{
		mlx_pixel_put(mlx, win, x1, y1, 0xFFFFFF);
		const int error2 = error * 2;
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
	mlx_loop(mlx);
	return (0);
}
