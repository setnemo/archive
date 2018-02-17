
#include "dns.h"
#include "support_func.h"
 
static int		check_malformed(t_buff *buffer)
{
	if (buffer->buffer[3] != 128) // проверяем флаги (128 это 1000 0000)
	{
		printf("[!] Query response Ox%x%x --malformed (drop)\n", buffer->buffer[2], buffer->buffer[1]);
		return (1);
	}
	return (0);
}

static void		udp(t_buff *buffer, int len, t_db *db)
{
	int sock;
	struct sockaddr_in socks_server;

	memset(&socks_server, 0, sizeof(socks_server));
	socks_server.sin_family = AF_INET;
	socks_server.sin_port = htons(db->port);
	socks_server.sin_addr.s_addr = inet_addr(db->forwarder);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) 
		error("[!] Error creating udp socket");
	if (connect(sock, (struct sockaddr*)&socks_server, sizeof(socks_server)) < 0)
		error("[!] Error connecting to proxy");

	srand(time(NULL));
	send(sock, buffer->buffer, len, 0);
	buffer->length = recv(sock, buffer->buffer, 2048, 0);
}

static void	listen_socket(t_db *db) {
	int					sock;
	char				len;
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
	printf("[*] Start DNS proxy.\n");

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
		// если пришел битый пакет - отправить его назад клиенту
		if ((check_blacklist(buffer->buffer, db, len)))
		{
			udp(buffer, len, db);
			//если вернулся битый пакет - цикл заново(так как протокол UDP)
			if (check_malformed(buffer))
				continue;
			sendto(sock, buffer->buffer, buffer->length, 0, (struct sockaddr *)&client, sizeof(client));
		}
		else
		{
			udp(buffer, len, db);
			sendto(sock, buffer->buffer, buffer->length, 0, (struct sockaddr *)&client, sizeof(client));
		}
		free(buffer->buffer);
		exit(0);
	}
}

void		start_dns(t_db *db)
{
	// хардкодим сокеты и порт
	db->listen = "0.0.0.0";
	db->sock = "127.0.0.1";
	db->port = 53;

	// запускаем чтение сокета
	listen_socket(db);
}
