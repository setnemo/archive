/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
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

void	mall_error(void)
{
	ft_printf("Error: Malloc fail!\n");
	exit(1);
}

void	print_usage(void)
{
	ft_printf("\033[1mUsage: ./corewar [-dump nbr_cycles] [-v] [-s]");
	ft_printf(" [-l lIdx] [[-n number] champion1.cor] ...\033[0m\n");
	ft_printf("   \033[1m-dump:\033[0m\n");
	ft_printf("\tafter nbr_cycles of executions, dump the memory on ");
	ft_printf("the standard output and quit the game\n");
	ft_printf("   \033[1m-v:\033[0m\n");
	ft_printf("\tvisual mod. \033[4mIncompatible with -l\033[0m\n");
	ft_printf("   \033[1m-l:\033[0m\n");
	ft_printf("\tlog mod.    \033[4mIncompatible with -v\033[0m\n");
	ft_printf("\t   1: commands log\n");
	ft_printf("\t   2: PC movement log\n");
	ft_printf("   \033[1m-n:\033[0m\n");
	ft_printf("\tcustom number of player\n");
	ft_printf("   \033[1m-s:\033[0m\n");
	ft_printf("\thide live messages\n");
	ft_printf("\033[1m\033[4mNOTE:\033[0m\033[1m The total number of players");
	ft_printf(" must be between 1 and %d\033[0m\n", MAX_PLAYERS);
	exit(0);
}

void	file_error(char *filename)
{
	ft_printf("\"%s\": %s\n", filename, strerror(errno));
	exit(0);
}
