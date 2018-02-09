/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:20:38 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 12:20:38 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

UC		b64manage(t_ssl *data, UC c, UC *temp)
{
	if ((c >= 'A') && (c <= 'Z'))
		return (c - 'A');
	else if ((c >= 'a') && (c <= 'z'))
		return (c - 'a' + 26);
	else if ((c >= '0') && (c <= '9'))
		return (c - '0' + 52);
	else if (c == '+')
		return (62);
	else if (c == '/')
		return (63);
	else if (c == '=')
		return (0);
	ft_printf("ERROR! Invalid charcter.\n");
	free(data->outcome);
	free(temp);
	exit(1);
}

UC	*b64_add(UC *inp, size_t *size)
{
	size_t			a;
	size_t			b;
	unsigned char	*out;

	a = 0;
	b = 0;
	if ((*size == 0) || (BASE64_LINE == 0))
		return (NULL);
	*size = *size + (*size / BASE64_LINE);
	if ((out = ft_memalloc(*size + 3)) == NULL)
		exit_error(errno, (inp));
	while (a < *size)
	{
		out[a++] = (inp)[b++];
		if (b % BASE64_LINE == 0)
			out[a++] = '\n';
	}
	if (out[(*size) - 1] != '\n')
		out[(*size)++] = '\n';
	return (out);
}

void	b64_del(t_ssl *data)
{
	size_t			a;
	size_t			b;

	a = 0;
	b = 0;
	if ((data->temp64 = ft_memalloc(data->size + 3)) == NULL)
		exit_error(errno, data->income);
	while (b < data->size)
	{
		if (data->income[b] == '\n')
			b++;
		else
			data->temp64[a++] = data->income[b++];
	}
	data->size = a;
}
