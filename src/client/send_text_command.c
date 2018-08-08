#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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

static char		*send_and_recv(const char *command, int sock_num)
{
	char		server_reply[4];
	char		*reply;
	int			len;

	command = insert_length(command, &len);
	if (send(sock_num, command, len, 0) < 0)
	{
		puts("Send failed");
		return (NULL);
	}
	puts("Sent");
	if (recv(sock_num, server_reply, 4, 0) < 0)
	{
		puts("ERROR recv");
		return (NULL);
	}
	len = *(int*)(&(server_reply[0]));
	printf("len: %d\n", len);
	reply = malloc(len + 1);
	if ((recv(sock_num, reply, len, 0)) < 0)
	{
		puts("ERROR second recv");
		return (NULL);
	}
	reply[len] = 0;
	puts("Received");
	return (reply);
}

char			*send_text_command(const char *command)
{
	int					sock_num;
	struct sockaddr_in	server;
	char				*server_reply;

	sock_num = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_num == -1)
		puts("Could not create socket!");
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(1337);
	if (connect(sock_num, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("Connection failed");
		return (NULL);
	}
	puts("Connected");
	server_reply = send_and_recv(command, sock_num);
	close(sock_num);
	return (server_reply);
}

int		main(void)
{
	char	*responce;

	responce = send_text_command("hello test\n");
	if (responce)
	{
		puts(responce);
	}
	free(responce);
	return (0);
}
