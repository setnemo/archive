
#include <stdio.h>
#include "read_config.h"

static int	valid_forwarder(t_db *db)
{
	int i;
	int dot;

	i = 0;
	dot = 0;


		if (db->forwarder[i] && db->forwarder[i] != '.' && (isdigit(db->forwarder[i]) == 0))
		{
			printf("[%c] Error: \n", db->forwarder[i]);
			return (1);
		}


		
	while (db->forwarder[i])
	{
		if (atoi(&db->forwarder[i]) == 0 && dot == 0)
		{
			printf("[!] Error: forwarder's IP can not start with 0\n");
			return (1);
		}
		if (atoi(&db->forwarder[i]) > 255)
		{
			printf("[!] Error: forwarder's IP incorrect\n");
			return (1);
		}
		if ((atoi(&db->forwarder[i]) == 255) && dot == 3)
		{
			printf("[!] Error: broadcast address\n");
			return (1);
		}

		//вайлим, пока существует строка и это цифра и это не точка
		while (db->forwarder[i] && isdigit(db->forwarder[i]))
			i++;
		//считаем точки, чтобы знать, где последний октет (вдруг он шириковещательный)
		if (db->forwarder[i] && db->forwarder[i] == '.')
			dot++;
		i++;
	}
	return (0);
}

// зафришить все, что существует в структуре и саму структуру
void		free_db(t_db *db)
{
	int i;

	i = 0;
	printf("free forwarder\n");
	if (db->forwarder)
		free(db->forwarder);
	printf("free listen\n");
	if (db->listen)
		free(db->listen);
	printf("free sock\n");
	if (db->sock)
		free(db->sock);
	printf("free blacklist\n");
	if (db->blacklist)
	{
		while(db->blacklist[i])
		{
			free(db->blacklist);
			i++;
		}
		free(db->blacklist);
	}
	printf("free db\n");
	free(db);
}

int			read_config(t_db *db)
{
	char	*tmp;
	char	*str;
	int		fd;
	int		i;

	fd = open(db->config, O_RDONLY);

	// если ошибка чтения - вернуть 0 (ошибка)
	if ((i = get_next_line(fd, &db->forwarder) < 0))
		return (0);

	// если форвардер не валидный - вернуть 0 (ошибка)
	if (valid_forwarder(db))
		return (0);

	// читаем остальные строки
	str = ft_strnew(0);
	while ((i = (get_next_line(fd, &tmp))))
	{
		str = ft_strjoin(str, tmp);
		str = ft_strjoin(str, "\n");
		free(tmp);
	}
	close(fd);

	//создаем массив строк
	db->blacklist = ft_strsplit(str, 10);

	//если URL не валидные - вернуть 0 (ошибка)
	// if (valid_url(db))
	// 	return (0);

	replace_dot(db);
	return (1);
}
