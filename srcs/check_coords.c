/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				check_coords_digits(char *line)
{
	int i;
	int sp;

	line = ft_strchr(line, 32);
	line++;
	sp = 1;
	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			i++;
		else if (sp && line[i] == 32)
			i++;
		else if (line[i] == 0 && sp == 0)
			return (0);
		else
			return (1);
	}
	return (0);
}

static int		valid_coords(t_lem *data, int i, int j, int *a)
{
	int		b[2];

	while (i < j)
	{
		if (data->validcoord[i] == NULL)
			break ;
		if (ft_strequ(data->validcoord[i], data->line) ||
			data->validcoord[i][0] == '#')
			i++;
		else
		{
			b[0] = ft_atoi(ft_strchr(data->validcoord[i], 32));
			b[1] = ft_atoi(ft_strrchr(data->validcoord[i], 32));
			if (a[0] == b[0] && a[1] == b[1])
				return (1);
			i++;
		}
	}
	return (0);
}

int				check_coords(t_lem *data, int i, int j)
{
	char	*p;
	int		a[2];

	i = data->startroomline - 1;
	p = data->input;
	// ft_printf("::::%s\n", data->line);
	a[0] = ft_atoi(ft_strchr(data->line, 32));
	a[1] = ft_atoi(ft_strrchr(data->line, 32));
	while (i)
	{
		if (*p == 10)
			i--;
		p++;
	}
	i = 0;
	j = ft_count_to_null((void**)p, 0) + 1;
	data->validcoord = ft_strsplit(p, 10);
	if (valid_coords(data, i, j, a))
		return (1);
	free_validcoord(data);
	return (0);
}
