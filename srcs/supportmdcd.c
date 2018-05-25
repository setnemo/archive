/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supportmdcd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 10:07:36 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 10:07:37 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#define SHA256S start_sha256(argv, data)
#define SHA512S start_sha512(argv, data)

void		string_md(t_md *data, char *argv, int *argc, int md)
{
	if (*argc)
	{
		*argc -= 1;
		if (md)
		{
			if (md == 1 || md == 2)
				(md == 1) ? SHA256S : SHA512S;
			else
				start_whirlpool(argv, data);
		}
		else
			start_md5(argv, data);
	}
	else
		ft_printf("./ft_ssl No args for flag \"-s\"\n");
}

void		before_start_md(char *argv, t_md *data, int md)
{
	// ft_printf("%i:%s\n", *argv);
	if (data->file && data->pfl != 2)
	{
		// ft_printf("====>"); //read STDIN here
		data->pfl = 1; // open stdin
	}
	if (md)
	{
		if (md == 1 || md == 2)
			(md == 1) ? SHA256S : SHA512S;
		else
			start_whirlpool(argv, data);
	}
	else
		start_md5(argv, data);
}

void		check_md_flags(int argc, char **argv, t_md *data, int md)
{
	while (argc--)
	{
		if (ft_strequ(*argv, "-r") && data->file)
			data->rfl = 1; // reverse on
		else if (ft_strequ(*argv, "-q") && data->file)
			data->qfl = 1; // silence on
		else if (ft_strequ(*argv, "-p") && data->file && data->pfl == 0)
			before_start_md("", data, md);
		else if (ft_strequ(*argv, "-s") && data->file == 1)
		{
			// ft_printf("NOW START READ -s\n");
			data->s = 1;
			string_md(data, *(++argv), &argc, md);
		}
		else
		{
			// ft_printf("NOW START READ FILE\n");
			data->file = 0; // off read -s and stdin
			before_start_md(*argv, data, md);
		}
		argv++;
	}
	data->howuse++;
	if (data->file == 1 && data->howuse == 1)
	{
		data->s = 1;
		data->howuse = 0;
		before_start_md("", data, md);
	}
}