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
  
	// socks handshake
	send(sock, "\x05\x01\x00", 3, 0);
	recv(sock, tmp, 1024, 0);

	srand(time(NULL));

	// select dns server
	in_addr_t remote_dns = inet_addr(db->forwarder);
	memcpy(tmp, "\x05\x01\x00\x01", 4);
	memcpy(tmp + 4, &remote_dns, 4);
	memcpy(tmp + 8, "\x00\x35", 2);


	send(sock, tmp, 10, 0);
	recv(sock, tmp, 1024, 0);

	// forward dns query
	send(sock, query, len, 0);
	buffer->length = recv(sock, buffer->buffer, 2048, 0);
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

	// create our udp listener
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		error("[!] Error setting up dns proxy");

	if(bind(sock, (struct sockaddr*)&listener, sizeof(listener)) < 0)
		error("[!] Error binding on dns proxy");

	printf("[*] No errors.\n");
	setuid(getpwnam("omentes")->pw_uid);
	setgid(getgrnam("omentes")->gr_gid);
	// daemonize the process.  , backgrounding process
	// if(fork() != 0) { exit(0); }
	// if(fork() != 0) { exit(0); }

	socklen_t client_size = sizeof(struct sockaddr_in);
	while(1)
	{
		// receive a dns request from the client
		len = recvfrom(sock, buffer->buffer, 2048, 0, (struct sockaddr *)&client, &client_size);
		
		int g = 0;
		ft_printf("paket! char:\n");
		while (g < 256)
			ft_printf("%c", buffer->buffer[g++]);
		ft_printf("\n");
		g = 0;
		ft_printf("paket! int:\n");
		while (g < 256)
			ft_printf(":%i:", buffer->buffer[g++]);
		ft_printf("\n");
		// lets not fork if recvfrom was interrupted
		if (len < 0 && errno == EINTR)
			continue;

		// fork so we can keep receiving requests
		if (fork() != 0)
			continue;
		// the tcp query requires the length to precede the packet, so we put the length there
		query = malloc(len + 3);
		query[0] = 0;
		query[1] = len;

		// check blacklist
		// if ((ft_check_black(buffer->buffer)))
		// {
		// 	sendto(sock, buffer->buffer + 2, buffer->length - 2, 0, (struct sockaddr *)&client, sizeof(client));
		// 	free(buffer->buffer);
		// 	free(buffer);
		// 	free(query);
		// 	continue;
		// }
		ft_memcpy(query + 2, buffer->buffer, len);

		// forward the packet to the tcp dns server

		tcp(query, buffer, len + 2, db);

		// send the reply back to the client (minus the length at the beginning)
		sendto(sock, buffer->buffer + 2, buffer->length - 2, 0, (struct sockaddr *)&client, sizeof(client));

		free(buffer->buffer);
		free(buffer);
		free(query);

		exit(0);
	}
}

static void		start(char *s, t_db *db)
{
	db->blacklist = ft_split(s);
	db->listen = "0.0.0.0";
	db->sock = "0.0.0.0";
	db->port = 53;

	if (getuid() != 0)
	{
		printf("Error: this program must be run as root! Quitting\n");
		exit(1);
	}
	printf("[*] Please wait...\n");

	// start the dns proxy
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
