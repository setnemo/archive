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

void			break_reading(t_lem *data, int error)
{
	if (data->error)
	{
		if (error == 8 || error == 9)
			(error == 8) ? ft_printf(ER08) : ft_printf(ER09);
	}
	else
		ft_printf("Error\n");
	ft_printf("[*] Stop reading data. Starting algorithm...\n");
}

static void		manage_error_11(int error)
{
	if (error == 12 || error == 13)
		(error == 12) ? ft_printf(ER12) : ft_printf(ER13);
	if (error == 14 || error == 15)
		(error == 14) ? ft_printf(ER14) : ft_printf(ER15);
	if (error == 16 || error == 17)
		(error == 16) ? ft_printf(ER16) : ft_printf(ER17);
	if (error == 18 || error == 19)
		(error == 18) ? ft_printf(ER18) : ft_printf(ER19);
	if (error == 20 || error == 21)
		(error == 20) ? ft_printf(ER20) : ft_printf(ER21);
	if (error == 22 || error == 23)
		(error == 22) ? ft_printf(ER22) : ft_printf(ER23);
}

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
		if (error == 10 || error == 11)
			(error == 10) ? ft_printf(ER10) : ft_printf(ER11);
		if (error > 11)
			manage_error_11(error);
	}
	else
		ft_printf("Error\n");
	if (data->showinput)
		ft_printf("%s", data->input);
	cleaning(data);
	exit(-42);
}

static void		initialize_data(t_lem *data)
{
	ft_bzero(data, sizeof(t_lem));
	data->showinput = 0;
	data->algo = 1;
	data->error = 0;
	data->in = 1;
	data->stop = 1;
	data->firstroomline = 1;
	data->input = NULL;
	data->validcoord = NULL;
	data->name_room = NULL;
	data->xy_rooms = NULL;
	data->temp = NULL;
	data->links = NULL;
	data->way = NULL;
	data->solve_path = NULL;
	data->tmp = NULL;
	data->toout = NULL;
}

int				main(int argc, char **argv)
{
	t_lem	*data;
	int		i;

	i = 0;
	if (argc > 4 && argv)
	{
		ft_printf("Error\n");
		exit(-42);
	}
	else
	{
		data = (t_lem*)malloc(sizeof(t_lem));
		ft_bzero(data, sizeof(t_lem));
		initialize_data(data);
		set_flags(data, ++argv, --argc);
	}
	manage_input(data);
	find_way(data);
	cleaning(data);
	return (0);
}
