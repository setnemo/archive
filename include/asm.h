/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:51:23 by apakhomo          #+#    #+#             */
/*   Updated: 2018/01/30 15:51:23 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "../libft/include/libft.h"
# include <unistd.h>
# include <fcntl.h>

typedef struct				s_asm
{
	size_t					len;
	int						fd;
	char					*dotsname;
	char					*dotsstr;
	char					*dotsstrtemp;
	int						dotcorfd;
	char					*dotcorname;
}							t_asm;

void						manage_error(t_asm *data, char error);

int							start_reading_file(t_asm *data);

void						start_reading_s(t_asm *data);

#endif
