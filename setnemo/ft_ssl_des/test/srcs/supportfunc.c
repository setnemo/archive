/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supportfunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:37:22 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 15:37:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

void		input_read(t_ssl *data)
{
	unsigned char	*newbuf;
	ssize_t			brk;

	if ((data->income = ft_memalloc(BUFFR)) == NULL)
		exit_error(errno, NULL);
	data->size = 0;
	brk = 1;
	while (brk != 0)
	{
		if ((brk = read(0, &data->income[data->size], 1024 - (data->size % 1024))) == -1)
			exit_error(errno, data->income);
		data->size += brk;
		if ((data->size) && (data->size % BUFFR == 0))
		{
			if ((newbuf = ft_memalloc(data->size + BUFFR)) == NULL)
				exit_error(errno, data->income);
			ft_memcpy(newbuf, data->income, data->size);
			free(data->income);
			data->income = newbuf;
			brk = 1;
		}
	}
}

unsigned char	*input_read_line(size_t *a)
{
	unsigned char	*buf;
	ssize_t			ret;

	if ((buf = ft_memalloc(128)) == NULL)
		exit_error(errno, NULL);
	*a = 0;
	ret = 1;
	while (ret != 0)
	{
		if ((ret = read(0, &buf[*a], 1)) == -1)
			exit_error(errno, buf);
		if (buf[*a] == '\n')
		{
			buf[*a] = 0;
			break ;
		}
		*a += ret;
		if (*a > 127)
			break ;
	}
	return (buf);
}

int				check_hex(unsigned char *str)
{
	int	i;

	i = 0;
	str = ft_strtolower(str);
	while (str[i] != 0)
	{
		if ((str[i] >= '0') && (str[i] <= '9'))
			i++;
		else if ((str[i] >= 'a') && (str[i] <= 'f'))
			i++;
		else
			return (0);
	}
	return (1);
}

unsigned long	hex_to_ul64(unsigned char *str)
{
	int				a;
	int				b;
	unsigned char	c;
	unsigned long	ret;

	str = ft_strtolower(str);
	a = 0;
	b = 0;
	ret = 0;
	while (a < 16)
	{
		c = str[b];
		if (str[b])
			b++;
		ret <<= 4;
		if ((c >= '0') && (c <= '9'))
			ret += (c - '0');
		if ((c >= 'a') && (c <= 'f'))
			ret += ((c - 'a') + 10);
		a++;
	}
	return (ret);
}
