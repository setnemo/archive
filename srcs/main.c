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

int		main(int argc, char **argv)
{
	t_mlx	*fdf;
	int		fd;

	if (argc == 2 && argv)
	{
		fdf = (t_mlx*)malloc(sizeof(t_mlx));
		fd = open(argv[1], O_RDONLY);
		read_map(fdf, fd);
//		ft_printf("test fdf\n");
		close(fd);
	}
	return (0);
}
