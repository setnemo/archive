
#include <sniffer.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

static void		sniffer()
{
	// тут будет код демона
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];
	 
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("sniffer Could not create socket");
	}
	puts("sniffer Socket created");
	 
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	 
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("sniffer bind failed. Error");
		exit(0);
	}
	puts("sniffer bind done");
	 
	//Listen
	listen(socket_desc , 3);
	 
	//Accept and incoming connection
	puts("sniffer Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	 
	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("sniffer accept failed");
		exit(0);
	}
	puts("sniffer Connection accepted");

	while (42)
	{
		read_size = recv(client_sock , client_message , 2000 , 0);
		if (read_size < 0 && errno == EINTR)
			continue;
		printf("[DAEMON]: I HAVE A DATA!!!!\n");
		read_size = 0;
		if(read_size == -1)
		{
			perror("sniffer recv failed");
		}
		// sleep(1);
		printf("sniffer Daemon work...\n");
	}
}

void			start_daemon(int *pid)
{
	*pid = fork();
	if (*pid == -1) // fork fail
	{
		printf("[!] Error! Start Daemon Error: %s\n", strerror(errno));
		exit(-42);
	}
	else if (!*pid)
	{
		// daemon settings
		umask(0);
		setsid();
		chdir("/");
		close(STDIN_FILENO);
		// close(STDOUT_FILENO);
		close(STDERR_FILENO);
		sniffer();
	}
}
