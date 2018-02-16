
#include <stdio.h>
#include "read_config.h"

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
			printf("free blacklist[%i]\n", i);
			free(db->blacklist[i]);
			i++;
		}
		free(db->blacklist);
	}
	printf("free db\n");
	free(db);
}

// проверяем валидность айпи форвардера
static int	valid_forwarder(t_db *db)
{
	int i;
	int dot;

	i = 0;
	// проверяем на сторонние символы (включая пробелы)
	while (db->forwarder[i])
	{
		if (db->forwarder[i] != '.' && (isdigit(db->forwarder[i]) == 0))
		{
			printf("[%c] Error: invalid character in IP\n", db->forwarder[i]);
			return (1);
		}
		i++;
	}
	i = 0;	
	dot = 0;
	// проверяем корректность айпи адреса
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
	if (dot > 3)
	{
		printf("[!] Error: forwarder's IP incorrect\n");
		return (1);
	}
	return (0);
}

static int	valid_url(t_db *db)
{
	char	rfc3986[] = ":/?#[]@!$&'()*+,;= ~";
	int		i;
	int		j;

	i = 0;
	while(db->blacklist[i])
	{
		j = 0;
		// проверяем, что первый символ не '-'
		if (db->blacklist[i][j] == '-')
		{
			printf("[!] Error: first charcter in domain name is '-'\n");
			return (1);
		}
		if (strlen(db->blacklist[i]) > 63)
		{
			printf("[!] Error: domain name length should not exceed 63 charcters\n");
			return (1);
		}
		while (db->blacklist[i][j])
		{
			// проверяем, что символ не заделарирован в стандрате rfc3986
			if (strchr(rfc3986, db->blacklist[i][j]))
			{
				printf("[!] Error: invalaid charcters in domain name\n");
				return (1);
			}
			//проверяем, что перед окончанием нет символа '-'
			if (db->blacklist[i][j + 1] != 0 && db->blacklist[i][j + 1] == '.' && db->blacklist[i][j] == '-')
			{
				printf("[!] Error: last charcter in word is '-'\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
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
	if (valid_url(db))
		return (0);

	replace_dot(db);
	return (1);
}
