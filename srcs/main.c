/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mines.h"

void		start_mines(t_data *data)
{
	if (data)
		;
}

int			main(void)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	// if (argc == 2)
	// {
	// 	if (ft_strequ("-h", argv[1]))
	// 		ft_printf("usage: %s command [command opts] [command args]\n", argv[0]);
	// 	return (1);
	// }
	start_mines(&data);
	return (0);
}
