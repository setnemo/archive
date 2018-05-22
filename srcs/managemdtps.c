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

#include "ft_ssl_des.h"

void			create_md_data(t_md *data)
{
	data->pfl = 1; // (STDIN) on
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
		before_start_md("тест", &data, md);
}

void		start_md5(char *argv, t_md *data)
{
	size_t	size;
	UC		*str;

	str = input_read(&size);
	ft_printf("%s\n", str);
	if (data || argv)
		ft_printf("start_md5 with:%s ITS ARG/STDIN:%i\n", argv, data->file);
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
