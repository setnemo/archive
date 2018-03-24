/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		add_new_path(t_lem *data, int i, int j, int *copy)
{
	int **path;
	int a;
	int b;

	path = data->way->path;
	a = 0;
	while (path[a])
		a++;
	// ft_printf("\n	while (path[a])\n");
	path[a] = (int*)malloc(sizeof(int) * (data->how_rooms + 1));
	ft_memset(path[a], -1, (sizeof(int) * (data->how_rooms + 1)));
	b = 0;
	// ft_printf("\nwhile (copy[b]\n");
	while (copy[b] != i)
	{
		path[a][b] = copy[b];
		b++;
	}
	// ft_printf("\nwhile (copy[b] != -1)\n");
	path[a][b] = i;
	path[a][b + 1] = j;
	// ft_printf("\naddnew done\n");
}

static int		search_room_in_path(int *path, int i, int j, int stop)
{
	int a;
	int flag;

	a = 0;
	flag = 0;
	if (path == NULL)
		return (0);
	while (a < stop)
	{
		if (path[a] == i)
		{
			if (path[a + 1] == -1)
			{
				flag = 1;
				path[a + 1] = j;
			}
			if (path[a + 1] != j)
				return (-1);
			if (path[a + 1] == j)
				return (0);
			else
				return (0);
		}
		a++;
	}
	return (flag ? 1 : 0);
}

static void		write_path(t_lem *data, int i, int j)
{
	int a;
	int b;
	int addnew;
	int flag;
	int **allpath;

	a = 0;
	allpath = data->way->path;
	flag = 0;
	addnew = 0;
	while (a < data->how_rooms)
	{
		while ((addnew = search_room_in_path(allpath[a], i, j, data->how_rooms)))
		{
			// ft_printf("\nsearch_room_in_path\n");
			if (addnew == -1){
				add_new_path(data, i, j, allpath[a]);
			}
			flag++;
			a++;	
		}
		a++;
	}
	if (flag == 0)
	{
		b = 0;
		if (i != data->start_room)
			return ;
		// ft_printf("\nflag == 0\n");
		while (allpath[b])
			b++;
		allpath[b] = (int*)malloc(sizeof(int) * (data->how_rooms + 1));
		ft_memset(allpath[b], -1, (sizeof(int) * (data->how_rooms + 1)));
		allpath[b][0] = i;
		allpath[b][1] = j;
	}
}

static int		new_room(int a, int *buf)
{
	int i;

	i = 0;
	while (buf[i] != -1)
	{
		if (buf[i] == a)
			return (0);
		i++;
	}
	return (1);
}

static void		bfs(t_lem *data, int i, int c, int *buf)
{
	int a;
	int b;

	b = 1;
	buf[c] = data->start_room;
	while (buf[c] != -1)
	{
		i = buf[c];
		// ft_printf("======================[%s]==>", data->name_room[buf[c]]);
		a = 0;
		while (a < data->how_rooms)
		{
			if (data->links[i][a] == 1 && data->links[a][data->how_rooms] != -1 && a != data->end_room)
			{
				if (new_room(a, buf))
				{
					buf[b] = a;
					write_path(data, i, a);
					// ft_printf(" [%s] ", data->name_room[buf[b]]);
					b++;
				}
			}
			if (data->links[i][a] == 1 && a == data->end_room)
			{
				write_path(data, i, a);
				// ft_printf("[%s] <<<<<", data->name_room[i]);
			}
			a++;
		}
		if (i != data->end_room)
		{
			data->links[i][data->how_rooms] = -1;
			// ft_printf(".\n");
		}
		c++;
	}
	ft_printf(":THE_END:\n");
}

void			find_way(t_lem *data)
{
	t_way		*ways;
	int			count;
	int			buf[data->how_rooms*data->how_rooms];

	count = 0;
	ways = (t_way*)malloc(sizeof(t_way));
	data->way = ways;
	ft_bzero(ways, sizeof(t_way));
	ft_memset(buf, -1, (sizeof(int) * (data->how_rooms + 1)));
	ways->path = ft_new_int_arr(data->how_rooms * data->how_rooms);
	//ft_printf("%s", data->input);
	ft_printf("data->how_ants [%i]\n", data->how_ants);
	ft_printf("data->start_room [%i]\n", data->start_room);
	ft_printf("data->end_room [%i]\n", data->end_room);
	ft_printf("data->how_rooms [%i]\n", data->how_rooms);
	bfs(data, data->start_room, 0, buf);
	manage_paths(data);
	// int k = 0, m = 0;
	// while (ways->path[k] != NULL)
	// {
	// 	while (m < data->how_rooms)
	// 	{
	// 		ft_printf(" [%s] ", ways->path[k][m]);
	// 		m++;
	// 	}
	// 	ft_printf("\n");
	// 	k++;
	// }
	// for (int k = 0; ways->path[k] != NULL; k++)
	// {
	// 	for (int m = 0; ways->path[k][m] != -1; ++m)
	// 		ft_printf(" [%s] ", data->name_room[ways->path[k][m]]);
	// 	ft_printf("\n");
	// }
}
