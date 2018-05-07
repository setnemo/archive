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
	data->pfl = 0;
	data->qfl = 0;
	data->rfl = 0;
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
			ft_printf(".%i.\n", md);
			if (md == 1 || md == 2)
				(md == 1) ? SHA256S : SHA512S;
			else
				start_whirlpool(argv, data);
		}
		else
		{
			ft_printf("2 start_md5:%s\n", argv[0]);
			start_md5(argv, data);
		}
	}
	else
		ft_printf("ft_ssl: md5: -s: No such file or directory\n");

}

void		check_md_flags(int argc, char **argv, t_md *data, int md)
{
	while (argc--)
	{
		if (ft_strequ(*argv, "-r") && data->rfl == 0)
			data->pfl = 1;
		else if (ft_strequ(*argv, "-p") && data->pfl == 0)
			data->pfl = 1;
		else if (ft_strequ(*argv, "-q") && data->qfl == 0)
			data->qfl = 1;
		else if (ft_strequ(*argv, "-s"))
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
			{
				ft_printf("start_md5:\"%s\"\n", *argv);
				start_md5(argv, data);
			}
		}
		argv++;
	}
}
