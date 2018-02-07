#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>
#include <grp.h>
#include "sdb.h"
#include <fcntl.h>

static void 	error(char *err)
{
	perror(err);
	exit(1);
}

static void		tcp(void *query, t_buff *buffer, int len, t_db *db) {
	int sock;
	struct sockaddr_in socks_server;
	char tmp[1024];

	memset(&socks_server, 0, sizeof(socks_server));
	socks_server.sin_family = AF_INET;
	socks_server.sin_port = htons(db->port);
	socks_server.sin_addr.s_addr = inet_addr(db->forwarder);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) 
		error("[!] Error creating TCP socket");
	if (connect(sock, (struct sockaddr*)&socks_server, sizeof(socks_server)) < 0)
		error("[!] Error connecting to proxy");
	in_addr_t remote_dns = inet_addr(db->forwarder);
	srand(time(NULL));
	send(sock, query, len, 0);
	buffer->length = recv(sock, buffer->buffer, 2048, 0);
}

static int			check_blacklist(char *buffer, t_db *db)
{
	int a;

	a = 0;
	while (db->blacklist[a])
	{			
		if (memcmp(buffer + 13, db->blacklist[a], ft_strlen(db->blacklist[a])) == 0)
			return (1);
		a++;
	}
	return (0);
}

static void			udp(t_db *db) {
	int					sock;
	char				len;
	char				*query;
	struct sockaddr_in	listener;
	struct sockaddr_in	client;

	t_buff *buffer = (t_buff*)malloc(sizeof(t_buff));
	buffer->buffer = malloc(2048);
	memset(&listener, 0, sizeof(listener));
	listener.sin_family = AF_INET;
	listener.sin_port = htons(db->port);
	listener.sin_addr.s_addr = inet_addr(db->listen);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		error("[!] Error setting up dns proxy");
	if(bind(sock, (struct sockaddr*)&listener, sizeof(listener)) < 0)
		error("[!] Error binding on dns proxy");
	ft_printf("[*] Start DNS proxy.\n");

	// daemonize the process.
	// if(fork() != 0) { exit(0); }
	// if(fork() != 0) { exit(0); }

	socklen_t client_size = sizeof(struct sockaddr_in);
	while(1)
	{
		len = recvfrom(sock, buffer->buffer, 2048, 0, (struct sockaddr *)&client, &client_size);
		if (len < 0 && errno == EINTR)
			continue;
		if (fork() != 0)
			continue;
		query = malloc(len + 3);
		query[0] = 0;
		query[1] = len;
		if ((check_blacklist(buffer->buffer, db)))
		{
			ft_memcpy(query + 2, buffer->buffer, len);
			tcp(query, buffer, len + 2, db);
			*(buffer->buffer + len + 3) = -129;
			*(buffer->buffer + len + 4) = 0;
			*(buffer->buffer + len + 5) = 0;
			*(buffer->buffer + len + 6) = 1;
			sendto(sock, buffer->buffer + 2, buffer->length - 2, 0, (struct sockaddr *)&client, sizeof(client));
		}
		else
		{
			ft_memcpy(query + 2, buffer->buffer, len);
			tcp(query, buffer, len + 2, db);
			sendto(sock, buffer->buffer + 2, buffer->length - 2, 0, (struct sockaddr *)&client, sizeof(client));
		}
		free(buffer->buffer);
		free(query);
		exit(0);
	}
}

static void		replace_dot(t_db *db)
{
	int		a;
	int		b;
	int		temp;
	char	*point;

	a = 0;
	while (db->blacklist[a])
	{
		b = 0;
		while (db->blacklist[a][b])
		{
			if (db->blacklist[a][b] == '.')
				{
					temp = b;
					point = &db->blacklist[a][b];
					b++;
					while (ft_isalnum(db->blacklist[a][b]))
						b++;
					*point = b - temp - 1;
					b--;
				}
			b++;
		}
		a++;
	}
}

static void		start(char *s, t_db *db)
{
	db->blacklist = ft_split(s);
	replace_dot(db);
	db->listen = "0.0.0.0";
	db->sock = "127.0.0.1";
	db->port = 53;

	if (getuid() != 0)
	{
		printf("Error: this program must be run as root! Quitting\n");
		exit(1);
	}
	printf("[*] Please wait...\n");
	udp(db);
}


int				main(void)
{
	t_db	*db;
	char	*tmp;
	char	*blacklist;
	int		fd;
	int		i;

	db = (t_db*)malloc(sizeof(t_db));
	fd = open("config.txt", O_RDONLY);
	get_next_line(fd, &db->forwarder);
	db->port = 53;
	ft_printf("[*] Use forwarder:%s:53\n", db->forwarder);
	blacklist = ft_strnew(0);
	while ((i = (get_next_line(fd, &tmp))))
	{
		blacklist = ft_strjoin(blacklist, tmp);
		blacklist = ft_strjoin(blacklist, "\n");
		ft_strdel(&tmp);
	}
	close(fd);
	start(blacklist, db);
    return (0);
}
