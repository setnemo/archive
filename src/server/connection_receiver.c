#include "server/server.h"

static char		*insert_length(const char *command, int *command_len)
{
	char		*tmp;
	int			len;

	len = strlen(command);
	tmp = strdup(command);
	tmp = realloc(tmp, len + 4);
	memmove((void*)(tmp + 4), (void*)tmp, len);
	tmp = memcpy((void*)tmp, (void*)&len, sizeof(int));
	*command_len = len + 4;
	return (tmp);
}

static int	bind_server(void)
{
	int					option;
	int					server_socket;
	struct sockaddr_in	server;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	option = 1;
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	if (server_socket == -1)
		perror("ERROR: Could not create server_socket!");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(1337);
	if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("ERROR: bind failed!");
		return (-1);
	}
	listen(server_socket, 3);
	return (server_socket);
}

static void	*client_handler(void *thread_data)
{
	int		client_socket;
	int		len;
	char	*buf;
	char	*responce;

	client_socket = *(int*)(thread_data);
	if (recv(client_socket, (char*)&len, sizeof(int), 0) != sizeof(int))
	{
		perror("ERROR: recv failed");
		return (NULL);
	}
	printf("len: %d\n", len);
	buf = malloc(len + 1);
	buf[len] = 0;
	if (recv(client_socket, buf, len, 0) != len)
	{
		perror("ERROR: invalid client data");
		return (NULL);
	}
	printf("Received: %s\n", buf);
	responce = command_handler(buf);
	free(buf);
	printf("Responded: %s\n", responce);
	responce = insert_length(responce, &len);
	write(client_socket, responce, len);
	close(client_socket);
	free(thread_data);
	free(responce);
	return (NULL);
}

static void	proccess_connection(int client_socket)
{
	pthread_t		client_thread;
	int				*thread_data;

	thread_data = malloc(sizeof(int));
	*thread_data = client_socket;
	pthread_create(&client_thread, NULL, client_handler, (void*)thread_data);
}

static void	wait_for_connection_loop(int server_socket)
{
	int						c;
	int						client_socket;
	struct sockaddr_in		client;

	c = sizeof(struct sockaddr_in);
	while ((client_socket =
		accept(server_socket, (struct sockaddr*)&client, (socklen_t*)&c)) > 0)
	{
		proccess_connection(client_socket);
	}
	if (client_socket < 0)
		perror("ERROR: accept failed");
}

void		receive_connection_loop(void)
{
	int		server_socket;

	server_socket = bind_server();
	printf("server_socket: %d\n", server_socket);
	if (server_socket < 0)
		return ;
	wait_for_connection_loop(server_socket);
}


int			main(void)
{
	receive_connection_loop();
}
