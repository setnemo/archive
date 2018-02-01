/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:49:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/01 14:49:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		count_len(char **mapstr)
{
	int a;

	a = 0;
	while (mapstr[a])
		a++;
	return (a);
}

static int		count_lenb(char *mapstr)
{
	int a;
	int count;

	a = 0;
	count = a;
	while (mapstr[a])
	{
		if (mapstr[a] && (ft_isdigit((int)mapstr[a]) == 1 || mapstr[a] == '-'))
		{
			count++;
			while (mapstr[a])
			{
				if (mapstr[a] == 32)
					break ;
				a++;
			}
		}
		a++;
	}
	return (count);
}

static void		str_to_int(t_mlx *fdf, char *mapstr, int a)
{
	int b;

	b = 0;
	fdf->map[a] = (int*)malloc(sizeof(int) * count_lenb(mapstr));
	while (*mapstr)
	{
		if ((ft_isdigit((int)mapstr[a])) || mapstr[a] == '-')
		{
			fdf->map[a][b] = atoi(mapstr);
			b++;
			while (*mapstr)
			{
				if (*mapstr == 32)
					break ;
				mapstr++;
			}
		}
		mapstr++;
	}
}

static void		arrstr_to_int(t_mlx *fdf, char **mapstr)
{
	int a;
	int len;

	a = 0;
	len = count_len(mapstr);
	fdf->map = (int**)malloc((sizeof(int*) * len) + 1);
	fdf->map[len] = NULL;
	while (mapstr[a])
	{
		str_to_int(fdf, mapstr[a], a);
		a++;
	}
}

void			read_map(t_mlx *fdf, int fd)
{
	char	*tmp;
	char	*maptmp;
	char	**mapstr;

	maptmp = ft_strnew(0);
	ft_printf("\nprint read:\n");
	while ((get_next_line(fd, &tmp)))
	{
		maptmp = ft_strjoin(maptmp, tmp);
		ft_printf("%s\n", tmp);
		maptmp = ft_strjoin(maptmp, "\n");
		ft_strdel(&tmp);
	}
	mapstr = ft_strsplit(maptmp, 10);
	arrstr_to_int(fdf, mapstr);
	ft_printf("\nprint fdf->map **int:\n");
	int lena = count_lenb(mapstr[0]);
	int lenb = count_len(mapstr);
	int a = 0;
	int b;
	while (a < lena)
	{
		b = 0;
		ft_printf("%i::: ", a);
		while (b < lenb)
		{
			ft_printf("%d ", fdf->map[a][b]);
			b++;
		}
		ft_printf("\n");
		a++;
	}
}
