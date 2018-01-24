#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "sdb.h"
#include <fcntl.h>

int		main(void)
{
	t_sdb	*list;
	t_sdb	*data;
	char	*forward;
	int		fd;

	fd = open("config.txt", O_RDONLY);
	get_next_line(fd, &forward);
	printf("%s\n", forward);
	list = (t_sdb*)malloc(sizeof(t_sdb));
	list->next = NULL;
	data = list;
	while ((get_next_line(fd, &data->addr)))
	{
		data->next = (t_sdb*)malloc(sizeof(t_sdb));
		data = data->next;
		data->addr = NULL;
		data->next = NULL;
	}
	close(fd);
	printf("%s\n%s\n", list->addr, list->next->addr);

	//test echo server with fork()
	
    return 0;
}