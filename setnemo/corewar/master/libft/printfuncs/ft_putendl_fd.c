/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:54:48 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 13:54:48 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_putendl_fd(char *str, int fd)
{
	size_t	ret;

	ret = ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	return (ret + 1);
}
