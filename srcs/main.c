
#include <stdio.h>
#include <strings.h>
#include "read_config.h"
#include "dns.h"

int				main(int argc, char **argv)
{
	t_db	*db;

	if (argc)
	{
		;
	}
	db = (t_db*)malloc(sizeof(t_db));
	bzero(db, sizeof(t_db));
	db->config = argv[1];
	// проверяем чтение файла, если ошибка - зафришить и выйти
	if (read_config(db))
	{
		printf("[*] Read config done!\n");
	}
	else
	{
		free_db(db);
		exit(1);
	}

	// проверяем рут (для чтения 53 порта нужен рут)
	if (getuid() != 0)
	{
		printf("[!] Error: this program must be run as root! Quitting\n");
		exit(1);
	}

	// запускаем днс прокси
	start_dns(db);
    return (0);
}
