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
	data->pfl = 1; // (STDIN) on
	data->qfl = 0; // silence off
	data->rfl = 0; // reverse off
	data->file = 1; // read "-s []" /"(STDIN)"
	data->inp = NULL;
	data->out = NULL;
}

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
		ft_printf("ft_ssl: md5: -s: No such file or directory\n");
}

void		before_start_md(char *argv, t_md *data, int md)
{
	if (data->file)
	{
		ft_printf("====>"); //read STDIN here
		data->pfl = 0; // close flag -p
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
		else if (ft_strequ(*argv, "-p") && data->file && data->pfl)
			before_start_md("STDIN", data, md);
		else if (ft_strequ(*argv, "-s") && data->file)
			string_md(data, *(++argv), &argc, md);
		else
		{
			data->file = 0; // off read -s and stdin
			before_start_md(*argv, data, md);
		}
		argv++;
	}
}