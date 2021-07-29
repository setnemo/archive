
#include <stdio.h>
#include "read_config.h"
#include "dns.h"

int				main(int argc, char **argv)
{
	t_db	*db;

	db = (t_db*)malloc(sizeof(t_db));
	memset(db, 0, sizeof(t_db));
	if (argc == 1)
		db->config = "config.txt";
	else if (argc == 2)
		db->config = argv[1];
	else
	{
		printf("[!] Error: Too many arguments\n");
		printf("[*] usage: %s                       --run with config.txt\n", argv[0]);
		printf("[*]        %s [path_to_config_file] --run with your config file\n", argv[0]);
		exit(1);
	}
	// проверяем чтение файла, если ошибка - зафришить и выйти
	if (read_config(db))
	{
		printf("[*] Read config done!\n");
	}
	else
	{
		//сборщик мусора
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
