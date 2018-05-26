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

#include "ft_ssl_des.h"
#include "ft_ssl_md5.h"
#include "ft_ssl_sha256.h"

void sha256init(t_sha256 *data)
{
	data->len[0] = 0;
	data->len[1] = 0;
	data->hash[0] = 0x6a09e667;
	data->hash[1] = 0xbb67ae85;
	data->hash[2] = 0x3c6ef372;
	data->hash[3] = 0xa54ff53a;
	data->hash[4] = 0x510e527f;
	data->hash[5] = 0x9b05688c;
	data->hash[6] = 0x1f83d9ab;
	data->hash[7] = 0x5be0cd19;
}

void		start_md(int argc, char **argv, int md)
{
	t_md	data;

	argc -= 2;
	argv += 2;
	ft_bzero(&data, sizeof(t_md));
	data.file = 1;
	if (argc)
		check_md_flags(argc, argv, &data, md);
	else
	{
		data.qfl = -1;
		data.pfl = 1;
		before_start_md("", &data, md);
	}
}

int		main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("usage: %s command [command opts] [command args]\n", argv[0]);
		return (1);
	}
	flag_parser(argc, argv, -1, 0);
	return (0);
}
