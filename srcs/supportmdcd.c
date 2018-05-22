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

#include "ft_ssl_des.h"
#define SHA256S start_sha256(argv, data)
#define SHA512S start_sha512(argv, data)

void		create_md_data(t_md *data)
{
	data->pfl = 1;
	data->qfl = 0; // silence off
	data->rfl = 0; // reverse off
	data->file = 1; //1 - STDIN, 0 - string, 2 - FILE?
	data->inp = NULL;
	data->out = NULL;
}

void		string_md(t_md *data, char **argv, int *argc, int md)
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
		ft_printf("ft_ssl: md5: -s: No such file or directory\n");
}

void		check_md_flags(int argc, char **argv, t_md *data, int md)
{
	while (argc--)
	{
		if (ft_strequ(*argv, "-r"))
			data->pfl = 0; // reverse on
		else if (ft_strequ(*argv, "-p") && data->pfl && data->file)
			data->pfl = 0;
		else if (ft_strequ(*argv, "-q"))
			data->qfl = 1; // silence on
		else if (ft_strequ(*argv, "-s") && data->file)
			string_md(data, ++argv, &argc, md);
		else
		{
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
		argv++;
	}
}