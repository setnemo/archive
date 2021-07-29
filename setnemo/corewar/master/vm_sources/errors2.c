/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:27:34 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:27:34 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "vm.h"

void	invalid_flag(char *str)
{
	ft_printf("Invalid flag: %s\n", str);
	exit(0);
}

void	not_a_champion(char *str)
{
	ft_printf("\"%s\" is not a champion!\n", str);
	system("afplay mp3/smile.mp3");
	exit(0);
}

void	invalid_palyer_index(char *str)
{
	ft_printf("Champion \"%s\" has an invalid number!\n", str);
	exit(0);
}

void	invalid_champion(char *str)
{
	ft_printf("Champion \"%s\" is invalid for some reason.\n", str);
	exit(0);
}

void	invalid_champ_length(char *str)
{
	ft_printf("Error: File %s has a code size ", str);
	ft_printf("that differ from what its header says.\n");
	exit(0);
}
