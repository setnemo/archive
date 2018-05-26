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
	int i;
	static t_ssl_mngr	(mngr[10]) = {
		{ .conver = "md5", .mngr = start_md },
		{ .conver = "sha256", .mngr = start_md },
		{ .conver = "whirlpool", .mngr = start_md },
		{ .conver = "base64", .mngr = start_base64 },
		{ .conver = "des", .mngr = start_ecb },
		{ .conver = "des-ecb", .mngr = start_ecb },
		{ .conver = "des-cbc", .mngr = start_cbc },
		{ .conver = "des3", .mngr = start_des3cbc },
		{ .conver = "des3-cbc", .mngr = start_des3cbc },
		{ .conver = "des3-ecb", .mngr = start_des3ecb },
		};

	i = 0;
	argv += 1;
	while (i < 10)
	{
		if (ft_strequ(*argv, mngr[i].conver))
			mngr[i].mngr(argc, argv, i);
		i++;
	}
}
// void	flag_parser1(int argc, char **argv)
// {
// 	if (ft_strequ(argv[1], "base64"))
// 		start_base64(argc, argv);
// 	else if ((ft_strequ(argv[1], "des")) || (ft_strequ(argv[1], "des-ecb")))
// 		start_ecb(argc, argv);
// 	else if (ft_strequ(argv[1], "des-cbc"))
// 		start_cbc(argc, argv);
// 	else if ((ft_strequ(argv[1], "des3")) || (ft_strequ(argv[1], "des3-cbc")))
// 		start_des3cbc(argc, argv);
// 	else if (ft_strequ(argv[1], "des3-ecb"))
// 		start_des3ecb(argc, argv);
// 	else if (ft_strequ(argv[1], "md5"))
// 		start_md(argc - 2, argv + 2, 0);
// 	else if (ft_strequ(argv[1], "sha256"))
// 		start_md(argc - 2, argv + 2, 1);
// 	else if (ft_strequ(argv[1], "whirlpool"))
// 		start_md(argc - 2, argv + 2, 2);
// 	else
// 		print_error(argv);
// }

void	read_input(t_ssl *data, UC **inp, size_t *size)
{
	if ((data->inp == NULL) || ((data->inp) && (ft_strequ(data->inp, "-"))))
	{
		*inp = input_read(size);
		if (*size < 1)
		{
			ft_printf("ERROR! No input data\n");
			exit(1);
		}
	}
	else
		*inp = readoutfile(data->inp, size);
}
