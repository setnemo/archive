/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:46:32 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:46:33 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

size_t	b64decode(UC *temp, t_ssl *data)
{
	size_t	a;
	size_t	b;
	UC		c;

	a = 0;
	b = 0;
	while (a < data->size)
	{
		data->outcome[b] = b64manage(data, temp[a++], temp) << 2;
		c = b64manage(data, temp[a++], temp);
		data->outcome[b++] += (c >> 4) & 0x3;
		data->outcome[b] = (c & 0xf) << 4;
		c = b64manage(data, temp[a++], temp);
		data->outcome[b++] += (c >> 2) & 0xf;
		data->outcome[b] = (c & 0x3) << 6;
		data->outcome[b++] += b64manage(data, temp[a++], temp) & 0x3f;
	}
	if ((temp[a - 1] == '=') && (temp[a - 2] == '='))
		data->outcome[--b] = 0;
	if (temp[a - 1] == '=')
		data->outcome[--b] = 0;
	return (b);
}

void	base64decode(t_ssl *data)
{
	size_t	a;

	b64_del(data);
	a = (data->size / 4) * 3;
	if ((data->outcome = ft_memalloc(a + 6)) == NULL)
	{
		free(data->temp64);
		exit_error(errno, data->income);
	}
	data->size = b64decode(data->temp64, data);
	free(data->temp64);
}

void	b64encode(t_ssl *data, UC *temp)
{
	size_t		a;
	size_t		b;
	UC			c;
	static char	*b64;

	a = 0;
	b = 0;
	b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	while (a < data->size)
	{
		temp[b++] = b64[data->outcome[a] >> 2];
		c = data->outcome[a++] << 6;
		temp[b++] = b64[(c >> 2) + (data->outcome[a] >> 4)];
		c = data->outcome[a++] << 4;
		temp[b++] = b64[(c >> 2) + (data->outcome[a] >> 6)];
		c = ((data->outcome[a++]) << 2);
		temp[b++] = b64[c >> 2];
	}
	if (a - 2 == data->size)
		temp[b - 2] = '=';
	if (a - 1 >= data->size)
		temp[b - 1] = '=';
}

void	base64encode(t_ssl *data)
{
	UC		*temp;
	size_t	size_temp;

	if ((data->outcome = ft_memalloc(data->size + 6)) == NULL)
		exit_error(errno, data->income);
	ft_memcpy(data->outcome, data->income, data->size);
	size_temp = data->size;
	while (size_temp % 3)
		size_temp++;
	size_temp /= 3;
	size_temp *= 4;
	if ((temp = ft_memalloc(size_temp + 1)) == NULL)
	{
		free(data->outcome);
		exit_error(errno, data->income);
	}
	b64encode(data, temp);
	free(data->outcome);
	(data->size) = size_temp;
	data->outcome = b64_add(temp, &data->size);
	free(temp);
}
