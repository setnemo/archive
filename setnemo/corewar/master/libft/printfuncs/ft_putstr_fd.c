/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:54:41 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 13:54:41 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

size_t	ft_putstr_fd(char *str, int fd)
{
	int		i;

	i = -1;
	if (str)
	{
		while (str[++i])
			write(fd, &str[i], 1);
		return (i);
	}
	else
		return (ft_putstr_fd("(null)", fd));
}
