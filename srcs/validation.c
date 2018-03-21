/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_lst		*lst_while(t_lem *data)
{
	t_lst		*income;

	income = data->next;
	while (income)
	{
		if (income->next)
			income = income->next;
		else
			break ;
	}
	if (income->flag == -1)
		return (income);
	else
	{
		income->next = (t_lst*)malloc(sizeof(t_lst));
		income = income->next;
		ft_bzero(income, sizeof(t_lst));
		income->flag = 0;
		income->next = NULL;
	}
	return (income);
}

static void			check_data(t_lem *data)
{
	t_lst		*income;

	write_input(data);
	if (data->stop)
	{
		income = lst_while(data);
 		income->str = ft_strdup(data->line);
		income->flag = 1; //определить что у нас там пришло и записать флаг 1 или 2
		// if (data->status == 1)
		// {

		// }
	}
}

void				manage_input(t_lem *data)
{
	t_lst		*income;

	income = (t_lst*)malloc(sizeof(t_lst));
	data->next = income;
	ft_bzero(income, sizeof(t_lst));
	income->flag = -1;
	income->next = NULL;
	if (get_next_line(STDIN_FILENO, &data->line) > 0)
	{
		data->input = ft_strjoin(data->line, "\n");
		check_ants(data, 0);
		while (get_next_line(STDIN_FILENO, &data->line) > 0 && data->stop)
		{
			check_data(data);
			ft_strdel(&data->line);
			if (data->start_count > 1)
				manage_error(data, 10);
			if (data->end_count > 1)
				manage_error(data, 11);
			if (data->stop == 0)
				break ;
		}
		ft_printf("=======>exit input\n");
		ft_printf("%s", data->input);
	}
	else
		manage_error(data, 0);
}
