/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manageflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:44:28 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:44:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "err.h"

void	error_flags(char *str)
{
	ft_printf("%s%s%s%s%s%s%s%s%s%s%s%s", ERP2);
	exit(1);
}

void	print_error(char **argv)
{
	ft_printf("%s%s%s%s%s%s%s", ERP1);
	exit(1);
}

void	exit_error(int err, void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_printf("%s\n", strerror(err));
	exit(1);
}

void	flag_parser(int argc, char **argv)
{
	if (ft_strequ(argv[1], "base64"))
		start_base64(argc, argv);
	else if ((ft_strequ(argv[1], "des")) || (ft_strequ(argv[1], "des-ecb")))
		start_ecb(argc, argv);
	// else if (ft_strequ(argv[1], "des-cbc"))
	// 	start_cbc(argc, argv);
	// else if ((ft_strequ(argv[1], "des3")) || (ft_strequ(argv[1], "des3-ecb")))
	// 	start_des3ecb(argc, argv);
	// else if (ft_strequ(argv[1], "des3-cbc"))
	// 	start_des3cbc(argc, argv);
	else
		print_error(argv);
}

void	read_input(t_ssl *data)
{
	if ((data->inp == NULL) || ((data->inp) && (ft_strequ(data->inp, "-"))))
	{
		input_read(data);
		if (data->size < 1)
		{
			ft_printf("ERROR! No input data\n");
			exit(1);
		}
	}
	else
		readoutfile(data);
}
