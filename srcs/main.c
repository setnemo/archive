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

    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024];
    int bytes_read;

    listener = socket(AF_INET, SOCK_DGRAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(53);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
        
        switch(fork())
        {
        case -1:
            perror("fork");
            break;
            
        case 0:
            close(listener);
            while(1)
            {
                bytes_read = recv(sock, buf, 1024, 0);
                if(bytes_read <= 0) break;
                send(sock, buf, bytes_read, 0);
            }

            close(sock);
            _exit(0);
            
        default:
            close(sock);
        }
    }
    
    close(listener);

    return 0;
	return (0);
}

// int main()
// {
//     int sock, listener;
//     struct sockaddr_in addr;
//     char buf[1024];
//     int bytes_read;

//     listener = socket(AF_INET, SOCK_STREAM, 0);
//     if(listener < 0)
//     {
//         perror("socket");
//         exit(1);
//     }
	
//     addr.sin_family = AF_INET;
//     addr.sin_port = htons(53);
//     addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
//     {
//         perror("bind");
//         exit(2);
//     }

//     listen(listener, 1);
	
//     while(1)
//     {
//         sock = accept(listener, NULL, NULL);
//         if(sock < 0)
//         {
//             perror("accept");
//             exit(3);
//         }

//         while(1)
//         {
//             bytes_read = recv(sock, buf, 1024, 0);
//             if(bytes_read <= 0) break;
//             printf(":%i\n", bytes_read);;
//         }
	
//         close(sock);
//     }
	
//     return 0;
// }