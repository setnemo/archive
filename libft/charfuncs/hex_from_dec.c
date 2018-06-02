/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_from_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:09:13 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/18 21:09:14 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	hex_from_dec(char *buf, _Bool is_cap)
{
	size_t	num;
	char	c;

	num = (buf[3] - '0') + (buf[2] - '0') * 2 +
			(buf[1] - '0') * 4 + (buf[0] - '0') * 8;
	if (num < 10)
		c = num + '0';
	else
	{
		num -= 10;
		if (is_cap)
			c = num + 'A';
		else
			c = num + 'a';
	}
	return (c);
}
