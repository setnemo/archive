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
#include "ft_ssl_sha256.h"
#include "ft_ssl_whirlpool.h"

int		start_md5a(char *argv, t_md *data, unsigned char **str)
{
	size_t	size;

	if (data->pfl == 1)
	{
		*str = input_read(&size);
		data->pfl = -1;
	}
	else if (data->file == 0)
	{
		if (open(argv, O_RDONLY) < 0)
		{
			ft_printf("./ft_ssl: %s : No such file or directory\n", argv);
			return (1);
		}
		*str = readoutfile(argv, &size);
	}
	else
		*str = (UC*)argv;
	return (0);
}

void		start_md5b(t_md *data, unsigned char *str, unsigned char *name)
{
	if (data->rfl == 0 && (data->qfl == 0 || data->qfl == -1))
	{
		if (data->pfl == -1 || data->qfl == -1)
		{
			if (data->rfl == 0 && data->qfl == -1)
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
	else if (data->rfl == 1 && data->pfl == -1 && data->s == 0 && data->howuse == 0)
	{
		ft_printf("%s", str);
	}
}

void		start_md5(char *argv, t_md *data)
{
	UC		*str;
	UC		*name;
	t_md5	md5data;
	UC		checksum[16];
	int		i;

	i = -1;
	if (start_md5a(argv, data, &str))
		return ;
	name = (UC*)argv;
	md5init(&md5data);
	md5update(&md5data, str, ft_strlen((char*)str));
	md5final(checksum, &md5data);
	start_md5b(data, str, name);
	while (++i < 16)
		ft_printf ("%02x", (unsigned int)checksum[i]);
	if (data->rfl == 1 && data->qfl == 0)
		(*name == 0) ? ft_printf ("") : (data->file == 1) ? ft_printf (" \"%s\"", name) : ft_printf (" %s", name);
	ft_printf ("\n");
	data->howuse++;
}

void		start_sha256(char *argv, t_md *data)
{
	UC			*str;
	UC			*name;
	t_sha256	context;
	uint8_t 	checksum[32];
	int			i;

	i = -1;
	if (start_md5a(argv, data, &str))
		return ;
	name = (UC*)argv;
	sha256init(&context);
	sha256hash(&context, (uint8_t*)str, (uint32_t)ft_strlen((char*)str));
	sha256done(&context, checksum, 0, 0);
	start_md5b(data, str, name);
	while (++i < 32)
		ft_printf ("%02x", checksum[i]);
	if (data->rfl == 1 && data->qfl == 0)
		(*name == 0) ? ft_printf ("") : (data->file == 1) ? ft_printf (" \"%s\"", name) : ft_printf (" %s", name);
	ft_printf ("\n");
	data->howuse++;
}

void		start_whirlpool(char *argv, t_md *data)
{
	UC		*str;
	UC		*name;
	UC		checksum[64];
	int		i;
 
	i = -1;
	if (start_md5a(argv, data, &str))
		return ;
	name = (UC*)argv;
	whirlpoolCompute((unsigned char*)str,ft_strlen((char*)str), (uint8_t*)checksum);
	start_md5b(data, str, name);
	while (++i < 64)
		ft_printf ("%02x", checksum[i]);
	if (data->rfl == 1 && data->qfl == 0)
		(*name == 0) ? ft_printf ("") : (data->file == 1) ? ft_printf (" \"%s\"", name) : ft_printf (" %s", name);
	ft_printf ("\n");
	data->howuse++;
}
