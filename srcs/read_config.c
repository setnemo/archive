
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "support_func.h"

static int	valid_forwarder(t_db *db)
{
	int i;
	int dot;

	i = 0;
	dot = 0;
	while (db->forwarder) // && db->forwarder[i] != 32 && (isdigit(db->forwarder[i])) || db->forwarder[i] == 
	{
		if (atoi(db->forwarder) == 0)
		{
			printf("[!] Error: forwarder's IP  can not start with 0\n");
			return (1);
		}
		if (atoi(db->forwarder) > 255)
		{
			printf("[!] Error: forwarder's IP incorrect\n");
			return (1);
		}
		if ((atoi(db->forwarder) == 255) && dot == 3)
		{
			printf("[!] Error: broadcast address\n");
			return (1);
		}
		while (db->forwarder && *db->forwarder != '.')
			db->forwarder++;
		if (db->forwarder && *db->forwarder == '.')
			dot++;
		db->forwarder++;
	}
	return (0);
}

void		free_db(t_db *db)
{
	int i;

	i = 0;
	if (db->forwarder)
		free(db->forwarder);
	if (db->listen)
		free(db->listen);
	if (db->sock)
		free(db->sock);
	if (db->blacklist)
	{
		while(db->blacklist[i])
		{
			free(db->blacklist);
			i++;
		}
		free(db->blacklist);
	}
	free(db);
}

int			read_config(t_db *db)
{
	char	*tmp;
	char	*blacklist;
	int		fd;
	int		i;

	fd = open("config.txt", O_RDONLY);

	// если ошибка чтения - вернуть 0 (ошибка)
	if ((i = get_next_line(fd, &db->forwarder) < 0));
		return (0);

	// если форвардер не валидный - вернуть 0 (ошибка)
	if (valid_forwarder(db))
		return (0);

	// читаем остальные строки
	blacklist = ft_strnew(0);
	while ((i = (get_next_line(fd, &tmp))))
	{
		blacklist = ft_strjoin(blacklist, tmp);
		blacklist = ft_strjoin(blacklist, "\n");
		free(tmp);
	}
	close(fd);

	//создаем массив строк
	db->blacklist = ft_split(s);

	//если URL не валидные - вернуть 0 (ошибка)
	if (valid_url(db))
		return (0);

	replace_dot(db);
	return (1);
}
