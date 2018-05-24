/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managemdtps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 10:07:36 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 10:07:37 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void			create_md_data(t_md *data)
{
	data->pfl = 0; // (STDIN) off
	data->qfl = 0; // silence off
	data->rfl = 0; // reverse off
	data->file = 1; // read "-s []" /"(STDIN)"
	data->inp = NULL;
	data->out = NULL;
}

void		start_md(int argc, char **argv, int md)
{
	t_md	data;

	create_md_data(&data);
	// ft_printf("%i:%s\n", argc, *argv);
	if (argc)
		check_md_flags(argc, argv, &data, md);
	else
	{
		data.qfl = -1;
		data.pfl = 1;
		before_start_md("тест", &data, md);
	}
}

void		start_md5(char *argv, t_md *data)
{
	size_t	size;
	UC		*str;
	UC		*name;
	t_md5 context;
	unsigned char checksum[16];
	int i;

	i = -1;
	// ft_printf("start_md5 with:%s data->file[%i], data->pfl[%i]\n", argv, data->file, data->pfl);
	if (data->pfl == 1)
	{
		str = input_read(&size);
		data->pfl = -1;
	}
	else if (data->file == 0)
		str = readoutfile(argv, &size);
	else
		str = (UC*)argv;
	name = (UC*)argv;
	// ft_printf("%s\n", str);
	md5init(&context);
	md5update(&context, str, ft_strlen((char*)str));
	md5final(checksum, &context);
		// ft_printf("\t\t\t\tdata->file[%i], data->rfl[%i], data->pfl[%i], data->qfl[%i]\n", data->file, data->rfl, data->pfl, data->qfl);
	if (data->rfl == 0 && (data->qfl == 0 || data->qfl == -1))
	{
		if (data->pfl == -1 || data->qfl == -1)
		{
			if (data->rfl == 0 && data->qfl == -1 && data->qfl == -1)
				data->pfl = -2;
			else
				ft_printf("%s", str);
			data->pfl = -2;
		}
		else if (data->qfl == -1)
		{
			data->qfl = 0;
			data->pfl = -2;
		}
		else
			(data->file == 1) ? ft_printf("MD5 (\"%s\") = ", str) : ft_printf("MD5 (%s) = ", name) ;
	}
	else if (data->rfl == 1 && data->pfl == -1 && data->qfl == 0)
	{
		ft_printf("%s", str);
	}
	while (++i < 16)
		ft_printf ("%02x", (unsigned int)checksum[i]);
	if (data->rfl == 1)
		(*name == 0) ? ft_printf ("") : ft_printf (" \"%s\"", name);
	ft_printf ("\n");
	// ft_printf("start_md5 with:%s data->file[%i], data->pfl[%i]\n", argv, data->file, data->pfl);
}

void		start_sha256(char *argv, t_md *data)
{
	size_t	size;
	UC		*str;

	str = input_read(&size);
	ft_printf("%s\n", str);
	if (data || argv)
		ft_printf("start_sha256 with:%s ITS ARG/STDIN:%i\n", argv, data->file);
}

void		start_sha512(char *argv, t_md *data)
{
	size_t	size;
	UC		*str;

	str = input_read(&size);
	ft_printf("%s\n", str);
	if (data || argv)
		ft_printf("start_sha512 with:%s ITS ARG/STDIN:%i\n", argv, data->file);
}

void		start_whirlpool(char *argv, t_md *data)
{
	size_t	size;
	UC		*str;

	str = input_read(&size);
	ft_printf("%s\n", str);
	if (data || argv)
		ft_printf("start_whirlpool with:%s ITS ARG/STDIN:%i\n", argv, data->file);
}
