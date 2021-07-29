/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_structures.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:24:14 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/08 17:24:15 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRUCTURES_H
# define LIBFT_STRUCTURES_H

# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_str
{
	char			*str;
	size_t			size;
}					t_str;

typedef struct		s_line
{
	int				r_bytes;
	char			*line;
	size_t			line_buf_size;
	size_t			line_size;
}					t_line;

typedef struct		s_read_arr
{
	char	**lines;
	size_t	size;
}					t_read_arr;

#endif
