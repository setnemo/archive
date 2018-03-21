/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	free_income(t_lst *income)
{
	t_lst *temp;

	while (income)
	{
		ft_printf("cleaning income lst\n");
		if (income->str)
			free(income->str);
		if (income->name)
			free(income->name);
		if (income->name2)
			free(income->name2);
		if (income->next)
		{
			temp = income;
			income = income->next;
			free(temp);
		}
		else
		{
			free(income);
			income = NULL;
		}
	}
}

void		cleaning(t_lem *data)
{
	if (data->input){
	ft_printf("cleaning data->input\n");
		free(data->input);
	}
	if (data->line){
	ft_printf("cleaning data->line\n");
		free(data->line);
	}
	if (data->temp){
	ft_printf("cleaning data->temp\n");
		free(data->temp);
	}
	if (data->next){
	ft_printf("cleaning data->next\n");
		free_income(data->next);
	}
	ft_printf("cleaning data\n");
	free(data);
	ft_printf("cleaning done\n");
}
