
#include "read_config.h"
#include "dns.h"

int				main(void)
{
	t_db	*db;

	db = (t_db*)malloc(sizeof(t_db));

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
