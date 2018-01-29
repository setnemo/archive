#include "sdb.h"
#include <fcntl.h>

static void 	error(char *err)
{
	perror(err);
	exit(1);
}

// from google - handle children
static void 	reaper_handle (int sig) {
	if (sig)
		while (waitpid(-1, NULL, WNOHANG) > 0)
			;
}


static void		tcp_query(void *query, response *buffer, int len) {
	int sock;
	struct sockaddr_in socks_server;
	char tmp[1024];

	memset(&socks_server, 0, sizeof(socks_server));
	socks_server.sin_family = AF_INET;
	socks_server.sin_port = htons(SOCKS_PORT);
	socks_server.sin_addr.s_addr = inet_addr(SOCKS_ADDR);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) 
		error("[!] Error creating TCP socket");

	if (connect(sock, (struct sockaddr*)&socks_server, sizeof(socks_server)) < 0)
		error("[!] Error connecting to proxy");
  
	// socks handshake
	send(sock, "\x05\x01\x00", 3, 0);
	recv(sock, tmp, 1024, 0);

	srand(time(NULL));

	// select random dns server
	in_addr_t remote_dns = inet_addr(dns_servers[rand() % (NUM_DNS - 1)]);
	memcpy(tmp, "\x05\x01\x00\x01", 4);
	memcpy(tmp + 4, &remote_dns, 4);
	memcpy(tmp + 8, "\x00\x35", 2);

	if (LOG == 1) { fprintf(LOG_FILE, "Using DNS server: %s\n", inet_ntoa(*(struct in_addr *)&remote_dns)); }

	send(sock, tmp, 10, 0);
	recv(sock, tmp, 1024, 0);

	// forward dns query
	send(sock, query, len, 0);
	buffer->length = recv(sock, buffer->buffer, 2048, 0);
}

static int			udp_listener() {
	int sock;
	char len, *query;
	response *buffer = (response*)malloc(sizeof(response));
	struct sockaddr_in dns_listener, dns_client;

	buffer->buffer = malloc(2048);

	memset(&dns_listener, 0, sizeof(dns_listener));
	dns_listener.sin_family = AF_INET;
	dns_listener.sin_port = htons(LISTEN_PORT);
	dns_listener.sin_addr.s_addr = inet_addr(LISTEN_ADDR);

	// create our udp listener
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		error("[!] Error setting up dns proxy");

	if(bind(sock, (struct sockaddr*)&dns_listener, sizeof(dns_listener)) < 0)
		error("[!] Error binding on dns proxy");

	FILE *resolv = fopen("/etc/resolv.conf", "w");

	if (!resolv)
		error("[!] Error opening /etc/resolv.conf");

	fprintf(resolv, "nameserver %s\n", LISTEN_ADDR);
	fclose(resolv);

	if (strcmp(LOGFILE, "/dev/null") != 0) 
	{
		LOG      = 1;
		LOG_FILE = fopen(LOGFILE, "a+");
		if (!LOG_FILE)
			error("[!] Error opening logfile.");
  }

	printf("[*] No errors, backgrounding process.\n");

	// daemonize the process.
	if(fork() != 0) { exit(0); }
	if(fork() != 0) { exit(0); }

	setuid(getpwnam(USERNAME)->pw_uid);
	setgid(getgrnam(GROUPNAME)->gr_gid);
	socklen_t dns_client_size = sizeof(struct sockaddr_in);

	// setup SIGCHLD handler to kill off zombie children
	struct sigaction reaper;
	memset(&reaper, 0, sizeof(struct sigaction));
	reaper.sa_handler = reaper_handle;
	sigaction(SIGCHLD, &reaper, 0);

	while(1)
	{
		// receive a dns request from the client
		len = recvfrom(sock, buffer->buffer, 2048, 0, (struct sockaddr *)&dns_client, &dns_client_size);

		// lets not fork if recvfrom was interrupted
		if (len < 0 && errno == EINTR) { continue; }

		// other invalid values from recvfrom
		if (len < 0)
		{
			if (LOG == 1)
				fprintf(LOG_FILE, "recvfrom failed: %s\n", strerror(errno));
			continue;
		}

	// fork so we can keep receiving requests
	if (fork() != 0) { continue; }

	// the tcp query requires the length to precede the packet, so we put the length there
	query = malloc(len + 3);
	query[0] = 0;
	query[1] = len;
	memcpy(query + 2, buffer->buffer, len);

	// forward the packet to the tcp dns server
	tcp_query(query, buffer, len + 2);

	// send the reply back to the client (minus the length at the beginning)
	sendto(sock, buffer->buffer + 2, buffer->length - 2, 0, (struct sockaddr *)&dns_client, sizeof(dns_client));

	free(buffer->buffer);
	free(buffer);
	free(query);

	exit(0);
	}
}

static void		start_config(char *s, t_db *db)
{
	db->bl = ft_split(s);
	db->l_addr = "0.0.0.0";
	db->l_prt = 53;

}


int				main(void)
{
	t_db	*db;
	char	*tmp;
	char	*bl;
	int		fd;
	int		i;

	db = (t_db*)malloc(sizeof(t_db));
	fd = open("config.txt", O_RDONLY);
	get_next_line(fd, &db->frw);
	db->frw_prt = 53;
	ft_printf("%s\n", db->frw);
	bl = ft_strnew(0);
	while ((i = (get_next_line(fd, &tmp))))
	{
		bl = ft_strjoin(bl, tmp);
		bl = ft_strjoin(bl, "\n");
		ft_strdel(&tmp);
	}
	close(fd);
	start_config(bl, db);
    return (0);
}
