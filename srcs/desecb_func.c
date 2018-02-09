/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desecb_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 14:10:05 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 14:10:06 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

unsigned char		*ft_strdup_uc(const unsigned char *s1)
{
	unsigned char	*new;
	size_t	x;
	size_t	a;

	a = 0;
	x = 0;
	while (s1[a] != '\0')
		a++;
	new = (unsigned char*)malloc(sizeof(unsigned char) * (a + 1));
	if (new == NULL)
		return (NULL);
	while (s1[x] != '\0')
	{
		new[x] = s1[x];
		x++;
	}
	new[x] = '\0';
	return (new);
}

void	ecb_show_key(t_ssl *data)
{
	int				a;
	unsigned char	c;

	a = 0;
	ft_printf("key=");
	while (a < 16)
	{
		c = (data->master_key >> (60 - (a * 4))) & 0xf;
		if (c < 10)
			c += '0';
		else
			c += ('a' - 10);
		write(1, &c, 1);
		a++;
	}
	ft_printf("\n");
}

void	ecb_e_inp(t_ssl *data)
{
	unsigned char	*temp;
	unsigned char	bit;
	size_t			a;

	a = ((data->size / 8) + 1) * 8;
	bit = a - data->size;
	if ((temp = ft_memalloc(a + 1)) == NULL)
		exit_error(errno, data->income);
	ft_memcpy(temp, data->income, data->size);
	free(data->income);
	data->income = temp;
	while (data->size < a)
		data->income[data->size++] = bit;
	ecb_core(&data->income, data->size, data->master_key, DES_E);
	if (data->b64 == 1)
	{
		base64encode(data);
		free(data->income);
	}
	else
		data->outcome = data->income;
}

void	ecb_d_inp(t_ssl *data)
{
	unsigned char	bit;
	size_t			a;

	if (data->b64 == 1)
	{
		base64decode(data);
		free(data->income);
		ft_bzero(data->income, ft_strlen((char*)data->income));
		data->income = ft_strdup_uc(data->outcome);
		free(data->outcome);
		ft_bzero(data->outcome, ft_strlen((char*)data->outcome));
	}
	ecb_core(&data->income, data->size, data->master_key, DES_D);
	bit = data->income[data->size - 1];
	if ((bit >= 1) && (bit <= 8))
	{
		a = data->size - bit;
		while (((data->income)[a] == bit) && (a < data->size))
			a++;
		if (a == data->size)
			data->size -= bit;
	}
	data->outcome = data->income;
}

void	ecb_hex_error(void *memory)
{
	if (memory != NULL)
		free(memory);
	ft_printf("ERROR! Non-hex digit\nInvalid hex key value\n");
	exit(1);
}

void		ecb_read_key(t_ssl *data)
{
	unsigned char	*str_key;
	unsigned long	size;

	if (data->key == NULL)
	{
		ft_printf("Type DES key in hex: ");
		str_key = input_read_line(&size);
		if (check_hex(str_key))
		{
			data->master_key = hex_to_ul64(str_key);
			free(str_key);
		}
		else
			ecb_hex_error(str_key);
	}
	else
	{
		if (check_hex((unsigned char *)data->key))
			data->master_key = hex_to_ul64((unsigned char *)data->key);
		else
			ecb_hex_error(NULL);
	}
	data->master_key = 0;
}
