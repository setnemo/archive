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
	path[a] = (int*)malloc(sizeof(int) * (data->how_rooms + 1));
	ft_memset(path[a], -1, (sizeof(int) * (data->how_rooms + 1)));
	b = 0;
	while (copy[b] != i)
	{
		path[a][b] = copy[b];
		b++;
	}
	path[a][b] = i;
	path[a][b + 1] = j;
}

static int		search_room_in_path(int *path, int i, int j, int stop)
{
	int a;
	int flag;

	a = -1;
	flag = 0;
	if (path == NULL)
		return (0);
	while (++a < stop)
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

static void		bfs(t_lem *data, t_bfs *bd, int *buf)
{
	buf[bd->c] = data->start_room;
	while (buf[bd->c] != -1)
	{
		bd->i = buf[bd->c];
		bd->a = 0;
		while (bd->a < data->how_rooms)
		{
			if (data->links[bd->i][bd->a] == 1 && data->links[bd->a][data->how_rooms] != -1 && bd->a != data->end_room)
			{
				if (new_room(bd->a, buf))
				{
					buf[bd->b] = bd->a;
					write_path(data, bd->i, bd->a);
					bd->b++;
				}
			}
			if (data->links[bd->i][bd->a] == 1 && bd->a == data->end_room)
				write_path(data, bd->i, bd->a);
			bd->a++;
		}
		if (bd->i != data->end_room)
			data->links[bd->i][data->how_rooms] = -1;
		bd->c++;
	}
}

void			find_way(t_lem *data)
{
	t_way		*ways;
	t_bfs		bd;
	int			count;
	int			buf[data->how_rooms*data->how_rooms];

	count = 0;
	ways = (t_way*)malloc(sizeof(t_way));
	data->way = ways;
	ft_bzero(ways, sizeof(t_way));
	ft_memset(buf, -1, (sizeof(int) * (data->how_rooms + 1)));
	ways->path = ft_new_int_arr(data->how_rooms * data->how_rooms);
	bd.a = 0;
	bd.b = 1;
	bd.c = 0;
	bd.i = data->start_room;
	bfs(data, &bd, buf);
	manage_paths(data);
}
