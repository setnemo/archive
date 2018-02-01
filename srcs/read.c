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
	int		count;
	char	**temp;

	count = 0;
	temp = ft_strsplit(mapstr, 32);
	while (temp[count] != NULL)
	{
		ft_printf("free? count:%i\n", count);
		free(temp[count]);
		ft_printf("free! count:%i\n", count);
		count++;
	}
	ft_printf("free? temp:?\n");
	free(temp);
	ft_printf("free!\n");
	return (count);
}

static void		str_to_int(t_mlx *fdf, char *mapstr, int a)
{
	int b;
	int c;

	b = 0;
	c = 0;
	fdf->map[a] = (int*)malloc(sizeof(int) * count_lenb(mapstr));
	while (mapstr[c] != 0)
	{
		if ((ft_isdigit((int)mapstr[c]) == 1 || mapstr[c] == '-'))
		{
			ft_printf(":::now is '%i', *mapstr = '%c'\n", a, mapstr[c]);
			fdf->map[a][b] = ft_atoi(mapstr + c);
			b++;
			while (mapstr[c] != 0 && mapstr[c] != 32)
				c++;
		}
		c++;
	}
	ft_printf("str_to_int exit\n");
}

static void		arrstr_to_int(t_mlx *fdf, char **mapstr)
{
	int a;
	int len;

	a = 0;
	len = count_len(mapstr);
	fdf->map = (int**)malloc((sizeof(int*) * len) + 1);
	fdf->map[len] = NULL;
	while (mapstr[a] != NULL)
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
	int lena = count_len(mapstr);
	int lenb = count_lenb(mapstr[0]);
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
