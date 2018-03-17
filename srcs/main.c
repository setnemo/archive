/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "error.h"

void			manage_error(t_lem *data, int error)
{
	if (data->error)
	{
		if (error == 0 || error == 1)
			(error == 1) ? ft_printf(ER00) : ft_printf(ER01);
		if (error == 2 || error == 3)
			(error == 2) ? ft_printf(ER02) : ft_printf(ER03);
		if (error == 4 || error == 5)
			(error == 4) ? ft_printf(ER04) : ft_printf(ER05);
		if (error == 6 || error == 7)
			(error == 6) ? ft_printf(ER06) : ft_printf(ER07);
		if (error == 8 || error == 9)
			(error == 8) ? ft_printf(ER08) : ft_printf(ER09);
		if (error == 10 || error == 11)
			(error == 10) ? ft_printf(ER10) : ft_printf(ER11);
		if (error == 12 || error == 13)
			(error == 12) ? ft_printf(ER12) : ft_printf(ER13);
	}
	else
		ft_printf("Error\n");
	cleaning(data);
	system("leaks -quiet lem-in");
	exit(-42);
}

static void		initialize_data(t_lem *data)
{
	ft_bzero(data, sizeof(t_lem));
	data->error = 1;
	data->in = 1;
	data->firstroomline = 1;
	data->input = NULL;
	data->validcoord = NULL;
	data->read_room = NULL;
	data->name_room = NULL;
	data->xy_rooms = NULL;
	data->rooms = NULL;
	data->temp = NULL;
	data->links = NULL;
	data->way = NULL;
	data->solve_path = NULL;
	data->tmp = NULL;
}

int				main(int argc, char **argv)
{
	t_lem *data;

	if (argc > 1 && argv)
	{
		ft_printf("Error\n");
		exit(-42);
	}
	data = (t_lem*)malloc(sizeof(t_lem));
	initialize_data(data);
	manage_input(data);
	// int i = 0;
	// int j;
	// while (i < data->how_rooms)
	// {
	// 	j = 0;
	// 	while (j < data->how_rooms)
	// 	{
	// 		ft_printf("%i ", data->links[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// 	ft_printf("\n");
	// }
	// ft_printf("CLEANING NOW, BITCHES\n");
	cleaning(data);
	// ft_printf("CLEANING DONE, BITCHES\n");
	system("leaks -quiet lem-in");
	return (0);
}
