/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_asm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:51:23 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/30 15:51:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_ASM_H
# define ERROR_ASM_H
# define AR AR1 == 'r' && AR2 == 'o' && AR3 == 'c' && AR4 == '.'
# define AR1 *(*argv + (data.len - 1))
# define AR2 *(*argv + (data.len - 2))
# define AR3 *(*argv + (data.len - 3))
# define AR4 *(*argv + (data.len - 4))
# define DDS "[*] Done! '%s' compiled to '%s'\n"
# define USAGE USAGE1, USAGE2, USAGE4
# define USAGE1 "usage: ./asm [filename1] [filename2] [filenameN]\n"
# define USAGE2 "       ./asm filename.s    compiled to filename.cor\n"
# define USAGE4 "       ./asm -h            show this message\n"

#endif
