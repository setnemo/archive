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

void		start_md(int argc, char **argv, int md)
{
	t_md	data;

	create_md_data(&data);
	check_md_flags(argc, argv, &data, md);
}

void		start_md5(char **argv, t_md *data)
{
	if (data || argv)
		;
}

void		start_sha256(char **argv, t_md *data)
{
	if (data || argv)
		;
}

void		start_sha512(char **argv, t_md *data)
{
	if (data || argv)
		;
}

void		start_whirlpool(char **argv, t_md *data)
{
	if (data || argv)
		;
}
