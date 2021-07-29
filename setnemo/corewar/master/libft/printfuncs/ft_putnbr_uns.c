/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:50:34 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/24 19:50:34 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"
#include <string.h>

size_t		ft_putnbr_uns(uintmax_t n)
{
	return (ft_putnbr_uns_fd(n, 1));
}
