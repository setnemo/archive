/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 11:34:28 by apakhomo          #+#    #+#             */
/*   Updated: 2017/11/19 11:34:29 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# define BUFF_SIZE 1
# define ERR(e) if (!e) return (-1);
# define NOMEM(no) if (!no) return (NULL);
# define ZERO(z) z = 0;

typedef struct		s_gnl
{
	int				fd;
	char			*str;
	char			*after;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
