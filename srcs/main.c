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

#include "asm.h"
#include "error_asm.h"

void				manage_error(t_asm *data, char error)
{
	if (error == 0 || error == 1)
		(error == 0) ? ft_printf(ER00) : ft_printf(ER01);
	if (error == 2 || error == 3)
		(error == 2) ? ft_printf(ER02) : ft_printf(ER03);
	if (error == 4 || error == 5)
		(error == 4) ? ft_printf(ER04) : ft_printf(ER05);
	if (error == 6 || error == 7)
		(error == 6) ? ft_printf(ER06) : ft_printf(ER07);
	if (error == 8 || error == 9)
		(error == 8) ? ft_printf(ER08) : ft_printf(ER09);
	if (data->dotsname)
		ft_strdel(&data->dotsname);
	if (data->dotcorname)
		ft_strdel(&data->dotcorname);
}

static void			init_data(t_asm *data)
{
	data->dotsname = NULL;
	data->dotcorname = NULL;
	data->dotsfd = -1;
	data->dotcorfd = -1;

}

int					main(int argc, char **argv)
{
	t_asm	data;

	init_data(&data);
	if (argc)
	{
		if (argc == 2)
			if (manage_argv(data, ++argv))
				manage_error(data, 0);
		else
			ft_printf(USAGE);
	}
	return (0);
}
