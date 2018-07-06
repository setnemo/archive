
#include <sniffer.h>

static void		sniffer()
{

	// тут будет код демона

	while (42)
	{
		sleep(1);
		printf("Daemon work...\n");
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
