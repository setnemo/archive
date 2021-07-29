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
#include "err.h"

void		print_error(char **argv)
{
	ft_printf("%s%s%s%s%s%s%s", ERP1);
	exit(1);
}

void		print_md_str2(t_md *data, unsigned char *name)
{
	if (*name == 0)
		ft_printf("");
	else
	{
		if (data->file == 1)
			ft_printf(" \"%s\"", name);
		else
			ft_printf(" %s", name);
	}
}

void		print_md_str(t_md *data, unsigned char *name, int md)
{
	char s[10];

	ft_bzero(&s[0], sizeof(char) * 10);
	if (md)
	{
		if (md == 1)
			ft_memcpy(&s[0], "SHA256", ft_strlen("SHA256"));
		else
			ft_memcpy(&s[0], "whirlpool", ft_strlen("whirlpool"));
	}
	else
		ft_memcpy(&s[0], "MD5", ft_strlen("MD5"));
	if (data->file == 1)
	{
		ft_printf("%s (\"%s\") = ", s, data->str);
	}
	else
	{
		ft_printf("%s (%s) = ", s, name);
	}
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

int			main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("usage: %s command [command opts] [command args]\n", argv[0]);
		return (1);
	}
	flag_parser(argc, argv, 0);
	return (0);
}
