/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_norm_mf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "error.h"
#define SZIDH sizeof(int) * (data->how_rooms + 1)
#define SRIPARG db.allpath[db.a], i, j, data->how_rooms

void			last_room(t_lem *data)
{
	data->in = 0;
	data->all = 0;
	if (data->start_count != 1 || data->end_count != 1)
		manage_error(data, 4);
	data->endroomline = data->countline + 1;
	data->xy_rooms = ft_new_int_arr(data->endroomline -
		data->startroomline + 1);
}

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

static void		init_wp_db(t_wp *db, t_lem *data, int flag1, int flag2)
{
	if (flag1 == -1 && flag2 == -1)
	{
		db->allpath = data->way->path;
		db->a = 0;
		db->flag = 0;
		db->addnew = 0;
		db->b = 0;
	}
	else
	{
		db->allpath[flag2] = (int*)malloc(SZIDH);
		ft_memset(db->allpath[flag2], -1, (SZIDH));
	}
}

void			write_path(t_lem *data, int i, int j)
{
	t_wp db;

	init_wp_db(&db, data, -1, -1);
	while (db.a < data->how_rooms)
	{
		while ((db.addnew = search_room_in_path(SRIPARG)))
		{
			if (db.addnew == -1)
				add_new_path(data, i, j, db.allpath[db.a]);
			db.flag++;
			db.a++;
		}
		db.a++;
	}
	if (db.flag == 0)
	{
		if (i != data->start_room)
			return ;
		while (db.allpath[db.b])
			db.b++;
		init_wp_db(&db, data, 1, db.b);
		db.allpath[db.b][0] = i;
		db.allpath[db.b][1] = j;
	}
}
