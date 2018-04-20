/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/21 16:09:10 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include <fcntl.h>

void    check_read_input(t_info *info, int ac, char **av)
{
    int     fd;
    int     i;

    i = 1;
    while (i < ac)
    {
        fd = open(av[i], O_RDONLY);
        if (fd < 0)
            printf("Error while opening file \"%s\"\n", av[i]);
        else
            save_file(info, fd);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_info  info;

    info = (t_info){0, 0, NULL};
    check_read_input(&info, argc, argv);
    return 0;
}