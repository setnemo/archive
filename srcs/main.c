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
#define ATDL (size_t)ft_atoi(data->line)

void				write_input(t_lem *data)
{
	if (data->line[0] == 0)
	{
		data->stop = 0;
		return ;
	}
	data->temp = ft_strjoin(data->input, data->line);
	ft_strdel(&data->input);
	data->input = ft_strjoin(data->temp, "\n");
	ft_strdel(&data->temp);
	data->countline++;
}

void				check_ants(t_lem *data, int i)
{
	if (data->line[0] == '#')
	{
		if (ft_strequ(data->line, "##start") || ft_strequ(data->line, "##end"))
			manage_error(data, ft_strequ(data->line, "##start") ? 16 : 17);
		ft_strdel(&data->line);
		while (get_next_line(STDIN_FILENO, &data->line) && data->line[0] == '#')
		{
			if (ft_strequ(data->line, "##start") || ft_strequ(data->line, "##end"))
				manage_error(data, ft_strequ(data->line, "##start") ? 16 : 17);
			write_input(data);
			ft_strdel(&data->line);
		}
		write_input(data);
	}
	while (ft_isdigit(data->line[i]))
		i++;
	(data->line[i] == 0) ? data->how_ants = ATDL : manage_error(data, 2);
	if (data->how_ants < 1)
		manage_error(data, 1);
	if (data->how_ants > 2143483647)
		manage_error(data, 3);
	if (ft_strlen(data->line) > 10)
		manage_error(data, 3);
	ft_strdel(&data->line);
	data->status = 1;
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
		if (error == 12 || error == 13)
			(error == 12) ? ft_printf(ER12) : ft_printf(ER13);
		if (error == 14 || error == 15)
			(error == 14) ? ft_printf(ER14) : ft_printf(ER15);
		if (error == 16 || error == 17)
			(error == 16) ? ft_printf(ER16) : ft_printf(ER17);
		if (error == 18 || error == 19)
			(error == 18) ? ft_printf(ER18) : ft_printf(ER19);
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
	data->stop = 1;
	data->countline = 1;
	data->input = NULL;
	data->temp = NULL;
	data->line = NULL;
	data->next = NULL;
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
	// ft_printf("CLEANING NOW, BITCHES\n");
	cleaning(data);
	// ft_printf("CLEANING DONE, BITCHES\n");
	system("leaks -quiet lem-in");
	return (0);
}
